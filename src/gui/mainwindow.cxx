#include <cmath>

#include <functional>
#include <limits>
#include <random>
#include <utility>
#include <vector>

#include <QBrush>
#include <QColor>
#include <QFont>
#include <QLocale>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPen>
#include <QString>
#include <QVector>
#include <QWheelEvent>
#include <QWidget>

#include "qcustomplot/qcustomplot.h"

#include "ui_mainwindow.h"

#include "mainwindow.hxx"
#include "../config.hxx"
#include "../math/functions.hxx"
#include "../math/mathutils.hxx"
#include "../math/numerictypes.hxx"
#include "../math/eulerodesolver.hxx"


#pragma region init/destroy

MainWindow::MainWindow (QWidget* parent) :
  QMainWindow (parent),
  ui_ (new Ui::MainWindow)
{
  ui_->setupUi (this);
//  initMainWindowSignalsAndSlots ();
  setDefaults ();
//  initCustomPlotSignalsAndSlots (ui_->plot_functions_CustomPlot);
  initCustomPlotSignalsAndSlots_2 (ui_->plot_functions_CustomPlot);
  initCustomPlot (ui_->plot_functions_CustomPlot);
  startingPoints_ = std::vector<Math::Point2D> ();
}


MainWindow::~MainWindow (void)
{
  delete ui_;
}

#pragma endregion // init/destroy


#pragma region private slots

void
MainWindow::on_funcParam_alpha_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_alpha_ = arg1;

  qDebug () << "funcParam_alpha_ ==" << funcParam_alpha_;

  setDirty (true);
}


void
MainWindow::on_funcParam_beta_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_beta_ = arg1;

  qDebug () << "funcParam_beta_ ==" << funcParam_beta_;

  setDirty (true);
}


void
MainWindow::on_funcParam_gamma_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_gamma_ = arg1;

  qDebug () << "funcParam_gamma_ ==" << funcParam_gamma_;

  setDirty (true);
}


void
MainWindow::on_funcParam_delta_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_delta_ = arg1;

  qDebug () << "funcParam_delta_ ==" << funcParam_delta_;

  setDirty (true);
}


void
MainWindow::on_funcParam_epsilon_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_epsilon_ = arg1;

  qDebug () << "funcParam_epsilon_ ==" << funcParam_epsilon_;

  setDirty (true);
}


void
MainWindow::on_funcParam_phi_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_phi_ = arg1;

  qDebug () << "funcParam_phi_ ==" << funcParam_phi_;

  setDirty (true);
}


void
MainWindow::on_plotParam_A_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::Gui::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 >= ui_->plotParam_B_DoubleSpinBox->value ())
    {
      ui_->plotParam_B_DoubleSpinBox->setValue (arg1 + Step);
    }

    plotParam_A_ = arg1;

    qDebug () << "plotParam_A_ ==" << plotParam_A_;

    setDirty (true);
  }
}


void
MainWindow::on_plotParam_B_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::Gui::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 <= ui_->plotParam_A_DoubleSpinBox->value ())
    {
      ui_->plotParam_A_DoubleSpinBox->setValue (arg1 - Step);
    }

    plotParam_B_ = arg1;

    qDebug () << "plotParam_B_ ==" << plotParam_B_;

    setDirty (true);
  }
}


void
MainWindow::on_plotParam_C_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::Gui::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 >= ui_->plotParam_D_DoubleSpinBox->value ())
    {
      ui_->plotParam_D_DoubleSpinBox->setValue (arg1 + Step);
    }

    plotParam_C_ = arg1;

    qDebug () << "plotParam_C_ ==" << plotParam_C_;

    setDirty (true);
  }
}


void
MainWindow::on_plotParam_D_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::Gui::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 <= ui_->plotParam_C_DoubleSpinBox->value ())
    {
      ui_->plotParam_C_DoubleSpinBox->setValue (arg1 - Step);
    }

    plotParam_D_ = arg1;

    qDebug () << "plotParam_D_ ==" << plotParam_D_;

    setDirty (true);
  }
}


void
MainWindow::on_solutionParam_n_SpinBox_valueChanged (int arg1)
{
  solutionParam_n_ = arg1;

  qDebug () << "solutionParam_n_ ==" << solutionParam_n_;

  setDirty (true);
}


void
MainWindow::on_solutionParam_tau_SpinBox_valueChanged (int arg1)
{
  solutionParam_tau_ = std::pow (10., double (arg1));

  qDebug () << "solutionParam_tau_ ==" << solutionParam_tau_;

  setDirty (true);
}


void
MainWindow::on_ctrl_plot_PushButton_clicked (void)
{
  qDebug() << "on_ctrl_plot_PushButton_clicked";

  updateCustomPlot (ui_->plot_functions_CustomPlot);
}


void
MainWindow::on_ctrl_reset_PushButton_clicked (void)
{
  qDebug() << "on_ctrl_reset_PushButton_clicked";

  startingPoints_.clear ();

  clearCustomPlot (ui_->plot_functions_CustomPlot);
}


void
MainWindow::on_ctrl_test_PushButton_clicked (void)
{
  std::random_device rd;
  std::mt19937 gen (rd ());
  std::uniform_real_distribution<double> dist_x (plotParam_A_, plotParam_B_);
  std::uniform_real_distribution<double> dist_y (plotParam_C_, plotParam_D_);

  quietModeEnabled_ = true;

  for (int i (0); i < 1000; ++i)
  {
    addStartingPoint (dist_x (gen), dist_y (gen));
  }

  quietModeEnabled_ = false;

  setDirty (true);
}


void
MainWindow::on_ctrl_liveUpdate_CheckBox_toggled (bool checked)
{
  liveUpdateEnabled_ = checked;

  qDebug () << "liveUpdateEnabled_ ==" << liveUpdateEnabled_;

  setDirty (true);
}


void
MainWindow::on_plot_functions_CustomPlot_selectionChangedByUser (void)
{
  QCustomPlot* const customPlot (qobject_cast<QCustomPlot*> (sender ()));

  if (
    customPlot->xAxis->selectedParts ().testFlag (QCPAxis::spAxis) ||
    customPlot->xAxis->selectedParts ().testFlag (QCPAxis::spTickLabels) ||
    customPlot->xAxis2->selectedParts ().testFlag (QCPAxis::spAxis) ||
    customPlot->xAxis2->selectedParts ().testFlag (QCPAxis::spTickLabels)
  )
  {
    customPlot->xAxis2->setSelectedParts (
      QCPAxis::spAxis | QCPAxis::spTickLabels
    );

    customPlot->xAxis->setSelectedParts (
      QCPAxis::spAxis | QCPAxis::spTickLabels
    );
  }

  if (
    customPlot->yAxis->selectedParts ().testFlag (QCPAxis::spAxis) ||
    customPlot->yAxis->selectedParts ().testFlag (QCPAxis::spTickLabels) ||
    customPlot->yAxis2->selectedParts ().testFlag (QCPAxis::spAxis) ||
    customPlot->yAxis2->selectedParts ().testFlag (QCPAxis::spTickLabels)
  )
  {
    customPlot->yAxis2->setSelectedParts (
      QCPAxis::spAxis | QCPAxis::spTickLabels
    );

    customPlot->yAxis->setSelectedParts (
      QCPAxis::spAxis | QCPAxis::spTickLabels
    );
  }

  for (int i (0); i < customPlot->plottableCount (); ++i)
  {
    QCPAbstractPlottable* const plottable (customPlot->plottable (i));
    QCPPlottableLegendItem* const item (
      customPlot->legend->itemWithPlottable (plottable)
    );

    if (item->selected () || plottable->selected ())
    {
      item->setSelected (true);
      plottable->setSelected (true);
    }
  }
}


void
MainWindow::on_plot_functions_CustomPlot_mousePress (QMouseEvent* ev)
{
  QCustomPlot* const customPlot (qobject_cast<QCustomPlot*> (sender ()));

  if (
    customPlot->xAxis->selectedParts ().testFlag (QCPAxis::spAxis)
  )
  {
    if (
      ev->type () == QEvent::MouseButtonPress &&
      ev->button () == Qt::LeftButton
    )
    {
      customPlot->axisRect ()->setRangeDrag (customPlot->xAxis->orientation ());
    }
  }
  else
  {
    if (
      customPlot->yAxis->selectedParts ().testFlag (QCPAxis::spAxis)
    )
    {
      if (
        ev->type () == QEvent::MouseButtonPress &&
        ev->button () == Qt::LeftButton
      )
      {
        customPlot->axisRect ()->setRangeDrag (
          customPlot->yAxis->orientation ()
        );
      }
    }
    else
    {
      customPlot->axisRect ()->setRangeDrag (Qt::Horizontal | Qt::Vertical);

      if (
        ev->type () == QEvent::MouseButtonPress &&
        ev->button () == Qt::RightButton
      )
      {
        const double x (customPlot->xAxis->pixelToCoord (ev->pos ().x ()));
        const double y (customPlot->yAxis->pixelToCoord (ev->pos ().y ()));

        qDebug () << "on_plot_functions_CustomPlot_mousePress" << x << y;

        addStartingPoint (x, y);
      }
    }
  }
}


void
MainWindow::on_plot_functions_CustomPlot_mouseWheel (QWheelEvent* ev)
{
  QCustomPlot* const customPlot (qobject_cast<QCustomPlot*> (sender ()));

  if (
    customPlot->xAxis->selectedParts ().testFlag (QCPAxis::spAxis)
  )
  {
    customPlot->axisRect ()->setRangeZoom (customPlot->xAxis->orientation ());
  }
  else
  {
    if (
      customPlot->yAxis->selectedParts ().testFlag (QCPAxis::spAxis)
    )
    {
      customPlot->axisRect ()->setRangeZoom (customPlot->yAxis->orientation ());
    }
    else
    {
      customPlot->axisRect ()->setRangeZoom (Qt::Horizontal | Qt::Vertical);
    }
  }
}


void
MainWindow::on_plot_functions_CustomPlot_mouseMove (QMouseEvent* ev)
{
  QCustomPlot* const customPlot (qobject_cast<QCustomPlot*> (sender ()));

  const double x (customPlot->xAxis->pixelToCoord (ev->pos ().x ()));
  const double y (customPlot->yAxis->pixelToCoord (ev->pos ().y ()));

  customPlot->setToolTip (QString ("(%1, %2)").arg (x).arg (y));
}

#pragma endregion // private slots


#pragma region private methods

[[deprecated("This is a workaround for strange autoconnection issues.")]]
void
MainWindow::initMainWindowSignalsAndSlots (void)
{
  connect (
    ui_->funcParam_alpha_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_alpha_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_beta_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_beta_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_gamma_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_gamma_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_delta_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_delta_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_phi_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_phi_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_epsilon_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_epsilon_DoubleSpinBox_valueChanged (double))
  );


  connect (
    ui_->plotParam_A_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_plotParam_A_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->plotParam_B_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_plotParam_B_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->plotParam_C_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_plotParam_C_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->plotParam_D_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_plotParam_D_DoubleSpinBox_valueChanged (double))
  );


  connect (
    ui_->solutionParam_n_SpinBox, SIGNAL (valueChanged (int)),
    this, SLOT (on_solutionParam_n_SpinBox_valueChanged (int))
  );

  connect (
    ui_->solutionParam_tau_SpinBox, SIGNAL (valueChanged (int)),
    this, SLOT (on_solutionParam_tau_SpinBox_valueChanged (int))
  );


  connect (
    ui_->ctrl_plot_PushButton, SIGNAL (clicked (void)),
    this, SLOT (on_ctrl_plot_PushButton_clicked (void))
  );

  connect (
    ui_->ctrl_reset_PushButton, SIGNAL (clicked (void)),
    this, SLOT (on_ctrl_reset_PushButton_clicked (void))
  );

  connect (
    ui_->ctrl_liveUpdate_CheckBox, SIGNAL (toggled (bool)),
    this, SLOT (on_ctrl_liveUpdate_CheckBox_toggled (bool))
  );
}


void
MainWindow::setDefaults (void)
{
  using namespace Config::Gui::Defaults;
  using namespace Config::Gui::InputLimits;


  quietModeEnabled_ = true;

  ui_->funcParam_alpha_DoubleSpinBox->setMinimum (FuncParam_Min);
  ui_->funcParam_alpha_DoubleSpinBox->setMaximum (FuncParam_Max);
  ui_->funcParam_alpha_DoubleSpinBox->setSingleStep (Step);
  ui_->funcParam_alpha_DoubleSpinBox->setValue (Alpha);

  ui_->funcParam_beta_DoubleSpinBox->setMinimum (FuncParam_Min);
  ui_->funcParam_beta_DoubleSpinBox->setMaximum (FuncParam_Max);
  ui_->funcParam_beta_DoubleSpinBox->setSingleStep (Step);
  ui_->funcParam_beta_DoubleSpinBox->setValue (Beta);

  ui_->funcParam_gamma_DoubleSpinBox->setMinimum (FuncParam_Min);
  ui_->funcParam_gamma_DoubleSpinBox->setMaximum (FuncParam_Max);
  ui_->funcParam_gamma_DoubleSpinBox->setSingleStep (Step);
  ui_->funcParam_gamma_DoubleSpinBox->setValue (Gamma);

  ui_->funcParam_delta_DoubleSpinBox->setMinimum (FuncParam_Min);
  ui_->funcParam_delta_DoubleSpinBox->setMaximum (FuncParam_Max);
  ui_->funcParam_delta_DoubleSpinBox->setSingleStep (Step);
  ui_->funcParam_delta_DoubleSpinBox->setValue (Delta);

  ui_->funcParam_phi_DoubleSpinBox->setMinimum (FuncParam_Min);
  ui_->funcParam_phi_DoubleSpinBox->setMaximum (FuncParam_Max);
  ui_->funcParam_phi_DoubleSpinBox->setSingleStep (Step);
  ui_->funcParam_phi_DoubleSpinBox->setValue (Phi);

  ui_->funcParam_epsilon_DoubleSpinBox->setMinimum (FuncParam_Min);
  ui_->funcParam_epsilon_DoubleSpinBox->setMaximum (FuncParam_Max);
  ui_->funcParam_epsilon_DoubleSpinBox->setSingleStep (Step);
  ui_->funcParam_epsilon_DoubleSpinBox->setValue (Epsilon);

  ui_->plotParam_A_DoubleSpinBox->setMinimum (ABCD_Min);
  ui_->plotParam_A_DoubleSpinBox->setMaximum (ABCD_Max);
  ui_->plotParam_A_DoubleSpinBox->setSingleStep (Step);
  ui_->plotParam_A_DoubleSpinBox->setValue (A);

  ui_->plotParam_B_DoubleSpinBox->setMinimum (ABCD_Min);
  ui_->plotParam_B_DoubleSpinBox->setMaximum (ABCD_Max);
  ui_->plotParam_B_DoubleSpinBox->setSingleStep (Step);
  ui_->plotParam_B_DoubleSpinBox->setValue (B);

  ui_->plotParam_C_DoubleSpinBox->setMinimum (ABCD_Min);
  ui_->plotParam_C_DoubleSpinBox->setMaximum (ABCD_Max);
  ui_->plotParam_C_DoubleSpinBox->setSingleStep (Step);
  ui_->plotParam_C_DoubleSpinBox->setValue (C);

  ui_->plotParam_D_DoubleSpinBox->setMinimum (ABCD_Min);
  ui_->plotParam_D_DoubleSpinBox->setMaximum (ABCD_Max);
  ui_->plotParam_D_DoubleSpinBox->setSingleStep (Step);
  ui_->plotParam_D_DoubleSpinBox->setValue (D);

  ui_->solutionParam_n_SpinBox->setMinimum (N_Min);
  ui_->solutionParam_n_SpinBox->setMaximum (N_Max);
  ui_->solutionParam_n_SpinBox->setValue (N);

  ui_->solutionParam_tau_SpinBox->setMinimum (TauExponent_Min);
  ui_->solutionParam_tau_SpinBox->setMaximum (TauExponent_Max);
  ui_->solutionParam_tau_SpinBox->setValue (TauExponent);

  ui_->ctrl_liveUpdate_CheckBox->setChecked (LiveUpdateEnabled);

  quietModeEnabled_ = false;
}


void
MainWindow::setDirty (bool isDirty)
{
  isDirty_ = isDirty;

  qDebug () << "isDirty_ ==" << isDirty_;

  if (isDirty_ && liveUpdateEnabled_ && !quietModeEnabled_)
  {
    // TODO: [~~] Update only parts of the plot that were modified.
    updateCustomPlot (ui_->plot_functions_CustomPlot);
  }
}


void
MainWindow::initCustomPlot (QCustomPlot* customPlot)
{
  using namespace Config::Gui::PlotParams;


  const QFont normalFont (font ().family (), FontSize);
//  const QFont boldFont (font ().family (), FontSize, QFont::Bold);

  customPlot->setInteractions (
    QCP::iRangeDrag | QCP::iRangeZoom |
    QCP::iSelectPlottables | QCP::iSelectAxes |
    QCP::iSelectLegend | QCP::iSelectItems
  );

  customPlot->setLocale (
    QLocale (QLocale::English, QLocale::UnitedStates)
  );

  customPlot->setAntialiasedElements (QCP::aeAll);

//  customPlot->legend->setVisible (true);
//  customPlot->legend->setFont (normalFont);
//  customPlot->legend->setSelectedFont (boldFont);
//  customPlot->legend->setSelectableParts (QCPLegend::spItems);

  customPlot->setAutoAddPlottableToLegend (true);

  customPlot->setBackgroundScaled (true);
  customPlot->setBackgroundScaledMode (Qt::IgnoreAspectRatio);

  customPlot->setPlottingHints (QCP::phForceRepaint | QCP::phCacheLabels);

  customPlot->xAxis2->setVisible (true);
  customPlot->xAxis2->setTickLabels (false);

  customPlot->yAxis2->setVisible (true);
  customPlot->yAxis2->setTickLabels (false);

  customPlot->xAxis->setSelectableParts (
    QCPAxis::spAxis | QCPAxis::spTickLabels
  );

  customPlot->yAxis->setSelectableParts (
    QCPAxis::spAxis | QCPAxis::spTickLabels
  );

  customPlot->xAxis->setRange (-1., 1.);
  customPlot->yAxis->setRange (-1., 1.);

  customPlot->xAxis->setLabel (QStringLiteral ("x"));
  customPlot->yAxis->setLabel (QStringLiteral ("y"));

  QCPPlotTitle* const plotTitle (new QCPPlotTitle (customPlot));
  plotTitle->setText (
    QStringLiteral (
      "#3 // Численное решение системы ОДУ //"
      " Алексей Горишный // группа ИТ-32БО"
    )
  );
  plotTitle->setFont (normalFont);
  customPlot->plotLayout ()->insertRow (0);
  customPlot->plotLayout ()->addElement (0, 0, plotTitle);
}


void
MainWindow::initCustomPlotSignalsAndSlots (QCustomPlot* customPlot)
{
  connect (
    customPlot, SIGNAL (selectionChangedByUser (void)),
    this, SLOT (on_plot_functions_CustomPlot_selectionChangedByUser (void))
  );

  connect (
    customPlot, SIGNAL (mousePress (QMouseEvent*)),
    this, SLOT (on_plot_functions_CustomPlot_mousePress (QMouseEvent*))
  );

  connect (
    customPlot, SIGNAL (mouseWheel (QWheelEvent*)),
    this, SLOT (on_plot_functions_CustomPlot_mouseWheel (QWheelEvent*))
  );

  connect (
    customPlot, SIGNAL (mouseMove (QMouseEvent*)),
    this, SLOT (on_plot_functions_CustomPlot_mouseMove (QMouseEvent*))
  );
}


void
MainWindow::initCustomPlotSignalsAndSlots_2 (QCustomPlot* customPlot)
{
  connect (
    customPlot->xAxis, SIGNAL (rangeChanged (QCPRange)),
    customPlot->xAxis2, SLOT (setRange (QCPRange))
  );

  connect (
    customPlot->yAxis, SIGNAL (rangeChanged (QCPRange)),
    customPlot->yAxis2, SLOT (setRange (QCPRange))
  );
}


void
MainWindow::enableCustomPlot (QCustomPlot* customPlot, bool enabled)
{
  if (enabled)
  {
    customPlot->setBackground (Qt::white);
  }
  else
  {
    customPlot->setBackground (Qt::lightGray);
  }

  customPlot->setEnabled (enabled);
}


void
MainWindow::clearCustomPlot (QCustomPlot* customPlot)
{
  customPlot->clearFocus ();
  customPlot->clearGraphs ();
  customPlot->clearItems ();
  customPlot->clearMask ();
  customPlot->clearPlottables ();

//  customPlot->plotLayout ()->remove (customPlot->plotLayout ()->element (0, 0));
//  customPlot->plotLayout ()->simplify ();

  customPlot->replot ();
}


void
MainWindow::updateCustomPlot (QCustomPlot* customPlot)
{
  using namespace Config::Gui::PlotParams;
  using Config::Gui::Colors;
  using std::placeholders::_1;
  using std::placeholders::_2;


  qDebug () << "updateCustomPlot";

  const QList<QString> colorNames (Colors.keys ());

  std::random_device rd;
  std::mt19937 gen (rd ());
  std::uniform_int_distribution<int> dist (0, colorNames.count () - 1);

  const std::function<Math::real_t (Math::real_t, Math::real_t)> f_1 (
    std::bind (
      Math::f_1, _1, _2, funcParam_alpha_, funcParam_beta_, funcParam_gamma_
    )
  );

  const std::function<Math::real_t (Math::real_t, Math::real_t)> f_2 (
    std::bind (
      Math::f_2, _1, _2, funcParam_delta_, funcParam_phi_, funcParam_epsilon_
    )
  );

  Math::EulerODESolver solver (solutionParam_tau_, f_1, f_2);

  clearCustomPlot (customPlot);

  for (const Math::Point2D& point : startingPoints_)
  {
    plotIntegralCurve (
      solver, point, solutionParam_n_,
      plotParam_A_, plotParam_B_, plotParam_C_, plotParam_D_,
      Colors[colorNames.at (dist (gen))],
      QString ("C(%1; %2)").arg (point.x).arg (point.y),
      customPlot
    );
  }

  plotBoundingBox (
    plotParam_A_, plotParam_B_, plotParam_C_, plotParam_D_,
    Qt::darkGray, customPlot
  );

  customPlot->rescaleAxes (true);

  customPlot->xAxis->setRange (plotParam_A_ - Margins, plotParam_B_ + Margins);
  customPlot->yAxis->setRange (plotParam_C_ - Margins, plotParam_D_ + Margins);

  customPlot->replot ();
}


void
MainWindow::addStartingPoint (Math::real_t x_0, Math::real_t y_0)
{
  startingPoints_.push_back (Math::Point2D { x_0, y_0 });

  qDebug () << "startingPoints_ += (" << x_0 << ";" << y_0 << ")";

  setDirty (true);
}


void
MainWindow::plotIntegralCurve (
  Math::EulerODESolver& solver,
  const Math::Point2D& startingPoint, int pointsCount,
  double keyStart, double keyEnd, double valueStart, double valueEnd,
  const QColor& color, const QString& name, QCustomPlot* customPlot
)
{
  QVector<double> keys (pointsCount), values (pointsCount), orders (pointsCount);

  solver.n (pointsCount / 2);
  solver.p_0 (startingPoint);

  solver.direction (Math::CurveDirection::Forward);
  {
    int idx (0);
    for (auto&& point : solver)
    {
      keys[idx] = point.x;
      values[idx] = point.y;
      orders[idx] = double (idx);
      ++idx;
    }
  }

  solver.n (pointsCount - pointsCount / 2);
  solver.direction (Math::CurveDirection::Backward);
  {
    int idx (pointsCount / 2);
    for (auto&& point : solver)
    {
      keys[idx] = point.x;
      values[idx] = point.y;
      orders[idx] = double (-idx + pointsCount / 2);
      ++idx;
    }
  }

//  solver.p_0 (startingPoint);

////  keys[0] = Math::clamp (keyStart, keyEnd, solver.p_0 ().x);
////  values[0] = Math::clamp (valueStart, valueEnd, solver.p_0 ().y);
//  keys[0] = solver.p_0 ().x;
//  values[0] = solver.p_0 ().y;
//  orders[0] = 0.;

//  solver.direction (Math::IntegralCurveDirection::Forward);
//  for (int n (1); n < pointsCount / 2 + 1; ++n)
//  {
//    solver.next ();

//    const Math::Point2D p_n_f (solver.p_n ());

////    keys[n] = Math::clamp (keyStart, keyEnd, p_n_f.x);
////    values[n] = Math::clamp (valueStart, valueEnd, p_n_f.y);
//    keys[n] = p_n_f.x;
//    values[n] = p_n_f.y;
//    orders[n] = double (n);
//  }

//  solver.direction (Math::IntegralCurveDirection::Backward);
//  for (int n (pointsCount / 2 + 1); n < pointsCount; ++n)
//  {
//    solver.next ();

//    const Math::Point2D p_n_b (solver.p_n ());

////    keys[n] = Math::clamp (keyStart, keyEnd, p_n_b.x);
////    values[n] = Math::clamp (valueStart, valueEnd, p_n_b.y);
//    keys[n] = p_n_b.x;
//    values[n] = p_n_b.y;
//    orders[n] = double (-n);
//  }

  QCPCurve* const integralCurve (
    new QCPCurve (customPlot->xAxis, customPlot->yAxis)
  );
  integralCurve->setData (orders, keys, values);
  integralCurve->setPen (QPen (color));
  integralCurve->setSelectedPen (
    QPen (QBrush (color), Config::Gui::PlotParams::SelectedPenWidth)
  );
  integralCurve->setName (name);
  customPlot->addPlottable (integralCurve);
}


void
MainWindow::plotBoundingBox (
  double keyStart, double keyEnd, double valueStart, double valueEnd,
  const QColor& color, QCustomPlot* customPlot
)
{
  QCPItemStraightLine* const top (new QCPItemStraightLine (customPlot));
  top->setPen (QPen (color));
  top->point1->setCoords (keyStart, valueEnd);
  top->point2->setCoords (keyEnd, valueEnd);
  top->setSelectable (false);
  top->setPen (QPen (Qt::DashLine));
  customPlot->addItem (top);

  QCPItemStraightLine* const bot (new QCPItemStraightLine (customPlot));
  bot->setPen (QPen (color));
  bot->point1->setCoords (keyStart, valueStart);
  bot->point2->setCoords (keyEnd, valueStart);
  bot->setSelectable (false);
  bot->setPen (QPen (Qt::DashLine));
  customPlot->addItem (bot);

  QCPItemStraightLine* const left (new QCPItemStraightLine (customPlot));
  left->setPen (QPen (color));
  left->point1->setCoords (keyStart, valueStart);
  left->point2->setCoords (keyStart, valueEnd);
  left->setSelectable (false);
  left->setPen (QPen (Qt::DashLine));
  customPlot->addItem (left);

  QCPItemStraightLine* const right (new QCPItemStraightLine (customPlot));
  right->setPen (QPen (color));
  right->point1->setCoords (keyEnd, valueStart);
  right->point2->setCoords (keyEnd, valueEnd);
  right->setSelectable (false);
  right->setPen (QPen (Qt::DashLine));
  customPlot->addItem (right);
}

#pragma endregion // private methods
