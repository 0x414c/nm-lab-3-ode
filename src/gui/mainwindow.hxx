#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX


#include <functional>
#include <vector>

#include <QColor>
#include <QMainWindow>
#include <QMouseEvent>
#include <QString>
#include <QWheelEvent>
#include <QWidget>

#include "qcustomplot/qcustomplot.h"

#include "../math/numerictypes.hxx"
#include "../math/eulerodesolver.hxx"


namespace Ui
{
  class MainWindow;
}


class MainWindow :
  public QMainWindow
{
  Q_OBJECT


  public:
    explicit MainWindow (QWidget* parent = nullptr);

    ~MainWindow (void);


  private slots:
    void on_funcParam_alpha_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_beta_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_gamma_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_delta_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_phi_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_epsilon_DoubleSpinBox_valueChanged (double arg1);

    void on_plotParam_A_DoubleSpinBox_valueChanged (double arg1);
    void on_plotParam_B_DoubleSpinBox_valueChanged (double arg1);
    void on_plotParam_C_DoubleSpinBox_valueChanged (double arg1);
    void on_plotParam_D_DoubleSpinBox_valueChanged (double arg1);

    void on_solutionParam_n_SpinBox_valueChanged (int arg1);
    void on_solutionParam_tau_SpinBox_valueChanged (int arg1);

    void on_ctrl_plot_PushButton_clicked (void);
    void on_ctrl_reset_PushButton_clicked (void);
    void on_ctrl_test_PushButton_clicked (void);
    void on_ctrl_liveUpdate_CheckBox_toggled (bool checked);

    void on_plot_functions_CustomPlot_selectionChangedByUser (void);
    void on_plot_functions_CustomPlot_mousePress (QMouseEvent* ev);
    void on_plot_functions_CustomPlot_mouseWheel (QWheelEvent* ev);
    void on_plot_functions_CustomPlot_mouseMove (QMouseEvent* ev);


  private:
    Ui::MainWindow* ui_ = nullptr;

    double funcParam_alpha_ = 0.;
    double funcParam_beta_ = 0.;
    double funcParam_gamma_ = 0.;
    double funcParam_delta_ = 0.;
    double funcParam_phi_ = 0.;
    double funcParam_epsilon_ = 0.;

    double plotParam_A_ = 0.;
    double plotParam_B_ = 0.;
    double plotParam_C_ = 0.;
    double plotParam_D_ = 0.;

    int solutionParam_n_ = 3;
    double solutionParam_tau_ = 0.;

    std::vector<Math::Point2D> startingPoints_;

//    Math::EulerODESolver odeSolver_;

    bool liveUpdateEnabled_ = false;
    bool quietModeEnabled_ = false;
    bool isDirty_ = false;

    void initMainWindowSignalsAndSlots (void);
    void setDefaults (void);

    void setDirty (bool isDirty = true);

    void initCustomPlot (QCustomPlot* customPlot);
    void initCustomPlotSignalsAndSlots (QCustomPlot* customPlot);
    void initCustomPlotSignalsAndSlots_2 (QCustomPlot* customPlot);
    void enableCustomPlot (QCustomPlot* customPlot, bool enabled = true);
    void clearCustomPlot (QCustomPlot* customPlot);
    void updateCustomPlot (QCustomPlot* customPlot);

    void addStartingPoint (Math::real_t x_0, Math::real_t y_0);

    void plotIntegralCurve (
      Math::EulerODESolver& solver,
      const Math::Point2D& startingPoint, int pointsCount,
      double keyStart, double keyEnd, double valueStart, double valueEnd,
      const QColor& color, const QString& name, QCustomPlot* customPlot
    );

    void plotBoundingBox (
      double keyStart, double keyEnd, double valueStart, double valueEnd,
      const QColor& color, QCustomPlot* customPlot
    );
};


#endif // MAINWINDOW_HXX
