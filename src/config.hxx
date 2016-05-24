#ifndef CONFIG_HXX
#define CONFIG_HXX


#include "globaldefinitions.hxx"

#include <utility>

#include <QColor>
#include <QMap>
#include <QString>

#include "math/numerictypes.hxx"


namespace Config
{
  namespace Gui
  {
    namespace Defaults
    {
//      constexpr double Alpha = 1.;
//      constexpr double Beta = 2.;
//      constexpr double Gamma = .5;
//      constexpr double Delta = 1.5;
//      constexpr double Phi = 1.;
//      constexpr double Epsilon = 1.;
      constexpr double Alpha = .1;
      constexpr double Beta = -.4;
      constexpr double Gamma = .2;
      constexpr double Delta = .2;
      constexpr double Phi = .4;
      constexpr double Epsilon = .1;

      constexpr double A = -1.75;
      constexpr double B = -0.25;
      constexpr double C = -1.;
      constexpr double D = 1.;

      constexpr int N = 750;
      constexpr int TauExponent = -2;

      constexpr bool LiveUpdateEnabled = true;
    }


    namespace InputLimits
    {
      constexpr double FuncParam_Min = -100.;
      constexpr double FuncParam_Max = 100.;

      constexpr double ABCD_Min = -100.;
      constexpr double ABCD_Max = 100.;

      constexpr int N_Min = 3;
      constexpr int N_Max = 10000;

      constexpr int TauExponent_Min = -4;
      constexpr int TauExponent_Max = 0;

      constexpr double Step = .1;
    }


    namespace PlotParams
    {
      constexpr int ResolutionMultiplier = 1;

      constexpr double Margins = 0.;

      constexpr double SelectedPenWidth = 2.;

      constexpr int FontSize = 9;
    }


    const QMap<QString, QColor> Colors {
      std::make_pair<QString, QColor> (QStringLiteral ("Red"), QColor (244, 67, 54)),
      std::make_pair<QString, QColor> (QStringLiteral ("Pink"), QColor (233, 30, 99)),
      std::make_pair<QString, QColor> (QStringLiteral ("Purple"), QColor (156, 39, 176)),
      std::make_pair<QString, QColor> (QStringLiteral ("DeepPurple"), QColor (103, 58, 183)),
      std::make_pair<QString, QColor> (QStringLiteral ("Indigo"), QColor (63, 81, 181)),
      std::make_pair<QString, QColor> (QStringLiteral ("Blue"), QColor (33, 150, 243)),
      std::make_pair<QString, QColor> (QStringLiteral ("LightBlue"), QColor (3, 169, 244)),
      std::make_pair<QString, QColor> (QStringLiteral ("Cyan"), QColor (0, 188, 212)),
      std::make_pair<QString, QColor> (QStringLiteral ("Teal"), QColor (0, 150, 136)),
      std::make_pair<QString, QColor> (QStringLiteral ("Green"), QColor (76, 175, 80)),
      std::make_pair<QString, QColor> (QStringLiteral ("LightGreen"), QColor (139, 195, 74)),
      std::make_pair<QString, QColor> (QStringLiteral ("Lime"), QColor (205, 220, 57)),
      std::make_pair<QString, QColor> (QStringLiteral ("Yellow"), QColor (255, 235, 59)),
      std::make_pair<QString, QColor> (QStringLiteral ("Amber"), QColor (255, 193, 7)),
      std::make_pair<QString, QColor> (QStringLiteral ("Orange"), QColor (255, 152, 0)),
      std::make_pair<QString, QColor> (QStringLiteral ("DeepOrange"), QColor (255, 87, 34)),
      std::make_pair<QString, QColor> (QStringLiteral ("Brown"), QColor (121, 85, 72)),
      std::make_pair<QString, QColor> (QStringLiteral ("Grey"), QColor (158, 158, 158)),
      std::make_pair<QString, QColor> (QStringLiteral ("BlueGrey"), QColor (96, 125, 139))
    };
  }


  namespace MathConstants
  {
#ifdef REAL_IS_BOOST_FLOAT128
    constexpr Math::real_t Epsilon = REAL_C (1E-32);
#else
#ifdef REAL_IS_GCC_FLOAT80
    constexpr Math::real_t Epsilon = REAL_C (1E-17);
#else
#ifdef REAL_IS_LONG_DOUBLE
    constexpr Math::real_t Epsilon = REAL_C (1E-17);
#else
#ifdef REAL_IS_DOUBLE
    constexpr Math::real_t Epsilon = REAL_C (1E-14);
#else
#ifdef REAL_IS_FLOAT
    constexpr Math::real_t Epsilon = REAL_C (1E-5);
#else
#error "`MathConstants::Epsilon' cannot be defined."
#endif // REAL_IS_FLOAT
#endif // REAL_IS_DOUBLE
#endif // REAL_IS_LONG_DOUBLE
#endif // REAL_IS_GCC_FLOAT80
#endif // REAL_IS_BOOST_FLOAT128
  }
}


#endif // CONFIG_HXX
