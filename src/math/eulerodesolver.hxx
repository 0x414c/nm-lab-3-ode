#ifndef EULERODESOLVER_HXX
#define EULERODESOLVER_HXX


#include <cstddef>

#include <functional>
#include <utility>

#include "numerictypes.hxx"


namespace Math
{
  class EulerODESolver;


  enum struct CurveDirection
  {
    Forward, Backward
  };


  struct Point2D
  {
    real_t x;
    real_t y;

    bool operator== (const Point2D& that) const;
    bool operator!= (const Point2D& that) const;
  };


  class SolutionIterator
  {
    public:
      SolutionIterator (EulerODESolver* solver = nullptr, size_t pos = 0);

      bool operator!= (const SolutionIterator& that) const;
      void operator++ (void);
      const Point2D& operator* (void) const;


    private:
      EulerODESolver* solver_;

      size_t pos_;
  };


  class EulerODESolver
  {
    public:
      EulerODESolver (
        real_t tau,
        const std::function<real_t (real_t, real_t)>& f_1,
        const std::function<real_t (real_t, real_t)>& f_2
      );

      size_t n (void) const;
      void n (size_t n);

      const Point2D& p_0 (void) const;
      void p_0 (real_t x_0, real_t y_0);
      void p_0 (const Point2D& p_0);

      const Point2D& p_n (void) const;

      CurveDirection direction (void) const;
      void direction (CurveDirection direction);

      void advance (void);
      void reset (void);

      SolutionIterator begin (void);
      SolutionIterator end (void);


    private:
      real_t tau_;
      size_t n_ = 0;

      Point2D p_0_;
      Point2D p_n_;

      CurveDirection direction_ = CurveDirection::Forward;

      std::function<real_t (real_t, real_t)> f_1_;
      std::function<real_t (real_t, real_t)> f_2_;
  };
}


#endif // EULERODESOLVER_HXX
