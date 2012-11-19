/**
 * @file pixel.h
 * @brief 
 * @author Dingjie.Wang (dingjie.wang@gmail.com)
 * @version 0.1
 * @date 2012-10-16
 */

#ifndef PIXEL_H

#define PIXEL_H


#include "m_opencv.h" 
#include <cmath>
#include "m_math.h"
using namespace m_opencv;

/**
 * @brief 
 */
/*class PixelGray {*/
/*public:*/
/*PixelGray(){ }*/
/*public:*/
/*void set_density(const GrayPixel &gray) {*/
/*_density.gray = gray;*/
/*}*/
/*GrayPixel get_gray( ) const {*/
/*return _density.gray;*/
/*}*/
/*RgbPixel get_rgb( ) const {*/
/*return _density.rgb;*/
/*}*/
/*double  get_density() const{*/
/*if (is_rgb()) */
/*return 0;   */
/*else*/
/*return _density.gray.v;*/
/*}*/
/*bool is_rgb() const { */
/*return _isRgb; */
/*}*/
/*static double density_distance(const Pixel &a, const Pixel &b){*/
/*return a.is_rgb() ? Pixel::_rgb_distance(a, b) :  Pixel::_gray_distance(a, b);*/
/*}*/

/*protected:*/
/*static double _gray_distance(const Pixel &a , const Pixel &b) {*/
/*return abs(a.get_gray().v - b.get_gray().v);*/
/*}*/
/*static  double _rgb_distance(const Pixel &a, const Pixel &b)  { return 0;}*/

/*union Density{*/
/*RgbPixel rgb;*/
/*GrayPixel gray;*/
/*};*/

/*public:*/
/*// two dimension force with index [homogeneity][spatial]*/
/*protected:*/
/*bool _isRgb;*/
/*Density _density;*/

/*}; */
/**
 * @brief 
 */
class GrayPixel2D{

    public:
        int _x;
        int _y;
    protected:
        GrayPixel _color;
    public:
        typedef GrayImage Image;
        typedef GrayPixel PixelType;
        GrayPixel2D(int x = 0 , int y = 0):_x(x), _y(y) { }
        void set_location(int x, int y){
            _x = x;
            _y = y;
        }
        static GrayPixel get_white(){
            GrayPixel white;
            white.v = 255;
            return white;
        }
        static double density_distance(const GrayPixel2D &a, const GrayPixel2D &b){
            return abs(a.get_density() - b.get_density());
        }
        static double spatial_distance(const GrayPixel2D &a, const GrayPixel2D &b){
            return (double)sqrt(pow(a._x - b._x, 2) +  pow(a._y - b._y, 2));
        }
        double get_density() const{
            return _color.v;
        }

        void set_color(const GrayPixel &gray){
            _color = gray;
        }
        GrayPixel  get_color() const{
            return _color;
        }
};

class RgbPixel2D {

    protected:
        RgbPixel _color;
    public:
        int _x;
        int _y;
        LuvPixel _luvColor;

    public:
        RgbPixel2D(int x = 0 , int y = 0):_x(x), _y(y) { }
        static double spatial_distance(const RgbPixel2D &a, const RgbPixel2D &b){
            return (double)sqrt(pow(a._x - b._x, 2) +  pow(a._y - b._y, 2));
        }
        void set_location(int x, int y){
            _x = x;
            _y = y;
        }
    public:

        typedef RgbImage Image;
        typedef RgbPixel PixelType;
        void set_color(const RgbPixel &rgb){
            _color = rgb;
            rgb2luv(_color.r, _color.g, _color.b, _luvColor);
        }
        double get_density( ) const{
            /*return _co*/
            return 0;
        }
        RgbPixel  get_color() const{
            return _color;
        }
        static double density_distance(const RgbPixel2D &a, const RgbPixel2D &b){
            /// @todo ...
            return m_math::length_edge(a._luvColor.l, a._luvColor.u, a._luvColor.v,
                    b._luvColor.l, b._luvColor.u, b._luvColor.v);
        }

        static RgbPixel get_white(){
            RgbPixel white;
            white.r = 255;
            white.g = 255;
            white.b = 255;
            return white;
        }

};

class GrayPixel3D{

    public:
        int _x;
        int _y;
        int _z;
        int _size;
    protected:
        GrayPixel _color;
    public:
        /*typedef GrayImage Image;*/
        typedef GrayPixel PixelType;
        GrayPixel3D(int x = 0, int y = 0, int z = 0):_x(x), _y(y), _z(z){ }

        GrayPixel3D(const GrayPixel &color, int x = 0 , int y = 0, int z = 0, int size = 0):_x(x), _y(y), _z(z),
        _size(size), _color(color) { }
        static double spatial_distance(const GrayPixel3D &a, const GrayPixel3D &b){
            return (double)sqrt(pow(a._x - b._x, 2) +  pow(a._y - b._y, 2) + pow(a._z - b._z, 2));
        }
        void set_location(int x, int y, int z){
            _x = x;
            _y = y;
            _x = z;
        }

        bool operator < (const GrayPixel3D &other) const{
            if (_x < other._x)
                return true;
            else if (_x > other._x)
                return false;
            else if (_y < other._y)
                return true;
            else if (_y > other._y)
                return false;
            else if (_z < other._z)
                return true;
            else 
                return false;
        }
        static GrayPixel get_white(){
            GrayPixel white;
            white.v = 255;
            return white;
        }
        static double density_distance(const GrayPixel3D &a, const GrayPixel3D &b){
            return abs(a.get_density() - b.get_density());
        }

        double get_density() const{
            return _color.v;
        }

        void set_color(const GrayPixel &gray){
            _color = gray;
        }
        GrayPixel  get_color() const{
            return _color;
        }
};

class RgbPixel3D {

    public:
        int _x;
        int _y;
        int _z;
        int _size;
        RgbPixel _color;

    public:

        RgbPixel3D(int x = 0, int y = 0, int z = 0):_x(x), _y(y), _z(z){ }

        RgbPixel3D(const RgbPixel &color, int x = 0 , int y = 0, int z = 0, int size = 0):_x(x), _y(y), _z(z),
        _size(size), _color(color) { }
        static double spatial_distance(const RgbPixel3D &a, const RgbPixel3D &b){
            return (double)sqrt(pow(a._x - b._x, 2) +  pow(a._y - b._y, 2) + pow(a._z - b._z, 2));
        }
        void set_location(int x, int y, int z){
            _x = x;
            _y = y;
            _x = z;
        }
        bool operator < (const RgbPixel3D &other) const{
            if (_x < other._x)
                return true;
            else if (_x > other._x)
                return false;
            else if (_y < other._y)
                return true;
            else if (_y > other._y)
                return false;
            else if (_z < other._z)
                return true;
            else 
                return false;
        }
    public:

        typedef RgbPixel PixelType;
        void set_color(const RgbPixel &rgb){
            _color = rgb;
        }
        double get_density( ) const{
            /*return _co*/
            return 0;
        }
        RgbPixel  get_color() const{
            return _color;
        }
        static double density_distance(const RgbPixel3D &a, const RgbPixel3D &b){
            // @bug temporal use, before find a way to measure the difference between two colors
            if (a.get_color() != b.get_color()) {
                return 1;
            }
            return 0;
        }

        static RgbPixel get_white(){
            RgbPixel white;
            white.r = 255;
            white.g = 255;
            white.b = 255;
            return white;
        }

};
typedef GrayPixel3D Block;
std::ostream& operator << (std::ostream& out, const GrayPixel2D& t);
std::ostream& operator << (std::ostream& out, const GrayPixel2D* t);
std::ostream& operator << (std::ostream& out, const RgbPixel2D& t);
std::ostream& operator << (std::ostream& out, const RgbPixel2D* t);
std::ostream& operator << (std::ostream& out, const GrayPixel3D& t);
std::ostream& operator << (std::ostream& out, const GrayPixel3D* t);
std::ostream& operator << (std::ostream& out, const RgbPixel3D& t);
std::ostream& operator << (std::ostream& out, const RgbPixel3D* t);
#endif /* end of include guard: PIXEL_H */