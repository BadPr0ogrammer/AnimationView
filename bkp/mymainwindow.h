#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>

class myMainWindow : public QMainWindow
{
  Q_OBJECT
  typedef QMainWindow Superclass;

public:
  myMainWindow();
  ~myMainWindow() override;

private:
  Q_DISABLE_COPY(myMainWindow)

  class pqInternals;
  QScopedPointer<pqInternals> Internals;
};

#endif // MYMAINWINDOW_H
