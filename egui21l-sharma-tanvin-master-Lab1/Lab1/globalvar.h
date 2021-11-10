#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include<QtGlobal>

QT_BEGIN_NAMESPACE
class QString;
class QJsonObject;
class QTimer;
QT_END_NAMESPACE



extern QJsonObject rootObj;
extern QStringList FinalRecipeList;
extern QTimer *timer;
extern QString currentItem;
extern QString FinalIngred;

#endif // GLOBALVAR_H
