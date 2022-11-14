#ifndef MYLOADDATAREACTION_H
#define MYLOADDATAREACTION_H

#include <pqLoadDataReaction.h>

class myLoadDataReaction : public pqLoadDataReaction
{
  Q_OBJECT
  typedef pqLoadDataReaction Superclass;

public:
  myLoadDataReaction(QAction* parent);

protected:
  void onTriggered() override;

private:
  Q_DISABLE_COPY(myLoadDataReaction)
};

#endif // MYLOADDATAREACTION_H
