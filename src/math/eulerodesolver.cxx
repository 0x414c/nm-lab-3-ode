#include <cstddef>

#include <functional>
#include <utility>

#include "eulerodesolver.hxx"
#include "numerictypes.hxx"


namespace Math
{
  bool
  Point2D::operator== (const Point2D& that) const
  {
    if (this == &that)
    {
      return true;
    }
    else
    {
      return (x == that.x && y == that.y);
    }
  }


  bool
  Point2D::operator!= (const Point2D& that) const
  {
    if (this == &that)
    {
      return false;
    }
    else
    {
      return (x != that.x || y != that.y);
    }
  }


  SolutionIterator::SolutionIterator (
    EulerODESolver* solver, size_t pos
  ) :
    solver_ (solver),
    pos_ (pos)
  { }


  bool
  SolutionIterator::operator!= (const SolutionIterator& that) const
  {
    if (this == &that)
    {
      return false;
    }
    else
    {
      return (solver_ != that.solver_ || pos_ != that.pos_);
    }
  }

  void
  SolutionIterator::operator++ (void)
  {
    ++pos_;
    solver_->advance ();
  }


  const Point2D&
  SolutionIterator::operator* (void) const
  {
    return solver_->p_n ();
  }


  EulerODESolver::EulerODESolver (
    real_t tau,
    const std::function<real_t (real_t, real_t)>& f_1,
    const std::function<real_t (real_t, real_t)>& f_2
  ) :
    tau_ (tau),
    f_1_ (f_1),
    f_2_ (f_2)
  { }


  size_t
  EulerODESolver::n (void) const
  {
    return n_;
  }


  void
  EulerODESolver::n (size_t n)
  {
    if (n_ != n)
    {
      n_ = n;
    }
  }

  const Point2D&
  EulerODESolver::p_0 (void) const
  {
    return p_0_;
  }


  void
  EulerODESolver::p_0 (real_t x_0, real_t y_0)
  {
    p_0 (Point2D { x_0, y_0 });
  }


  void
  EulerODESolver::p_0 (const Point2D& p_0)
  {
    if (p_0_ != p_0)
    {
      p_0_ = p_0;

      reset ();
    }
  }


  const Point2D&
  EulerODESolver::p_n (void) const
  {
    return p_n_;
  }


  CurveDirection
  EulerODESolver::direction (void) const
  {
    return direction_;
  }

  void
  EulerODESolver::direction (CurveDirection direction)
  {
    if (direction_ != direction)
    {
      direction_ = direction;

      reset ();
    }
  }


  void
  EulerODESolver::advance ()
  {
    switch (direction_)
    {
      case CurveDirection::Forward:
        p_n_.x += tau_ * f_1_ (p_n_.x, p_n_.y);
        p_n_.y += tau_ * f_2_ (p_n_.x, p_n_.y);

        break;

      case CurveDirection::Backward:
        p_n_.x -= tau_ * f_1_ (p_n_.x, p_n_.y);
        p_n_.y -= tau_ * f_2_ (p_n_.x, p_n_.y);

        break;

      default:
        break;
    }
  }


  void
  EulerODESolver::reset (void)
  {
    if (p_n_ != p_0_)
    {
      p_n_ = p_0_;
    }
  }


  SolutionIterator
  EulerODESolver::begin (void)
  {
    reset ();

    return SolutionIterator (this);
  }


  SolutionIterator
  EulerODESolver::end (void)
  {
    return SolutionIterator (this, n_);
  }
}
