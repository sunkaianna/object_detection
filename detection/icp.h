/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2010, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id: icp.h 6149 2012-07-04 22:54:14Z rusu $
 *
 */

#ifndef PCL_ICP_H_
#define PCL_ICP_H_

// PCL includes
#include <pcl/sample_consensus/ransac.h>
#include <pcl/sample_consensus/sac_model_registration.h>
#include <pcl/registration/registration.h>
#include <pcl/registration/transformation_estimation_svd.h>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <algorithm>
#include <limits>
#include "emd.h"
using namespace pcl;
class VizBlockWorld;

/** \brief @b IterativeClosestPoint provides a base implementation of the Iterative Closest Point algorithm. 
 * The transformation is estimated based on Singular Value Decomposition (SVD).
 *
 * The algorithm has several termination criteria:
 *
 * <ol>
 * <li>Number of iterations has reached the maximum user imposed number of iterations (via \ref setMaximumIterations)</li>
 * <li>The epsilon (difference) between the previous transformation and the current estimated transformation is smaller than an user imposed value (via \ref setTransformationEpsilon)</li>
 * <li>The sum of Euclidean squared errors is smaller than a user defined threshold (via \ref setEuclideanFitnessEpsilon)</li>
 * </ol>
 *
 *
 * Usage example:
 * \code
 * IterativeClosestPoint<PointXYZ, PointXYZ> icp;
 * // Set the input source and target
 * icp.setInputCloud (cloud_source);
 * icp.setInputTarget (cloud_target);
 *
 * // Set the max correspondence distance to 5cm (e.g., correspondences with higher distances will be ignored)
 * icp.setMaxCorrespondenceDistance (0.05);
 * // Set the maximum number of iterations (criterion 1)
 * icp.setMaximumIterations (50);
 * // Set the transformation epsilon (criterion 2)
 * icp.setTransformationEpsilon (1e-8);
 * // Set the euclidean distance difference epsilon (criterion 3)
 * icp.setEuclideanFitnessEpsilon (1);
 *
 * // Perform the alignment
 * icp.align (cloud_source_registered);
 *
 * // Obtain the transformation that aligned cloud_source to cloud_source_registered
 * Eigen::Matrix4f transformation = icp.getFinalTransformation ();
 * \endcode
 *
 * \author Radu Bogdan Rusu, Michael Dixon
 * \ingroup registration
 */
template <typename PointSource, typename PointTarget>
class IterativeClosestPoint : public Registration<PointSource, PointTarget>
{

    public:
        typedef typename Registration<PointSource, PointTarget>::PointCloudSource PointCloudSource;
        typedef typename PointCloudSource::Ptr PointCloudSourcePtr;
        typedef typename PointCloudSource::ConstPtr PointCloudSourceConstPtr;

        typedef typename Registration<PointSource, PointTarget>::PointCloudTarget PointCloudTarget;

        typedef PointIndices::Ptr PointIndicesPtr;
        typedef PointIndices::ConstPtr PointIndicesConstPtr;
        typedef boost::bimaps::bimap< int, int > BiMap;
        typedef BiMap::value_type BiValue;
        /** \brief Empty constructor. */
        IterativeClosestPoint () 
        {
            reg_name_ = "IterativeClosestPoint";
            ransac_iterations_ = 1000;
            transformation_estimation_.reset (new pcl::registration::TransformationEstimationSVD<PointSource,
                                                        PointTarget>);
            autoResponse_ = true;
            flow_ = NULL;
            pre_EMD_ = std::numeric_limits<float>::max();
            best_EMD_ = std::numeric_limits<float>::max();
        };

        ~IterativeClosestPoint () {
            if (flow_) {
                delete []flow_;
            }
        }
        void setInputWeight(const std::vector<float> &wInput);
        void setOutputWeight(const std::vector<float> &wOutput);
        const BiMap& get_correspondence() const{
            return myCorrespondence_;
        }
        void visualize_correspondence(VizBlockWorld *viz, int view) const;
        //! set correspondences between two points set
        inline void set_correspondence(const BiMap &input) {
            myCorrespondence_.clear();
            std::copy(input.begin(), input.end(), back_inserter(myCorrespondence_));
            autoResponse_ = false;
        }

    protected:
        /** \brief Rigid transformation computation method  with initial guess.
         * \param output the transformed input point cloud dataset using the rigid transformation found
         * \param guess the initial guess of the transformation to compute
         */
        virtual void 
            computeTransformation (PointCloudSource &output, const Eigen::Matrix4f &guess);

        using Registration<PointSource, PointTarget>::reg_name_;
        using Registration<PointSource, PointTarget>::getClassName;
        using Registration<PointSource, PointTarget>::input_;
        using Registration<PointSource, PointTarget>::indices_;
        using Registration<PointSource, PointTarget>::target_;
        using Registration<PointSource, PointTarget>::nr_iterations_;
        using Registration<PointSource, PointTarget>::max_iterations_;
        using Registration<PointSource, PointTarget>::ransac_iterations_;
        using Registration<PointSource, PointTarget>::previous_transformation_;
        using Registration<PointSource, PointTarget>::final_transformation_;
        using Registration<PointSource, PointTarget>::transformation_;
        using Registration<PointSource, PointTarget>::transformation_epsilon_;
        using Registration<PointSource, PointTarget>::converged_;
        using Registration<PointSource, PointTarget>::corr_dist_threshold_;
        using Registration<PointSource, PointTarget>::inlier_threshold_;
        using Registration<PointSource, PointTarget>::min_number_correspondences_;
        using Registration<PointSource, PointTarget>::update_visualizer_;
        using Registration<PointSource, PointTarget>::correspondence_distances_;
        using Registration<PointSource, PointTarget>::euclidean_fitness_epsilon_;
        using Registration<PointSource, PointTarget>::transformation_estimation_;
        std::vector<float> wInput_;
        std::vector<float> wOutput_;
        PointCloudSource *output_;
    public:
        // input -> output, Bimap make sure one to one correspondence
        BiMap myCorrespondence_;
        float pre_EMD_;
        bool autoResponse_;
        flow_t *flow_;
        float best_EMD_;
};

#include "icp.hpp" 

#endif  //#ifndef PCL_ICP_H_
