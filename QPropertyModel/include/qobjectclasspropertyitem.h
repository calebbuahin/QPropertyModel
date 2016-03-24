#ifndef QOBJECTCLASSPROPERTYITEM_H
#define QOBJECTCLASSPROPERTYITEM_H

#include "qpropertyitem.h"
#include <QMetaObject>

class QPROPERTYMODEL_EXPORT QObjectClassPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      Q_INVOKABLE QObjectClassPropertyItem(QObject* value, const QMetaObject* metaObject, QPropertyItem * parent);

      virtual ~QObjectClassPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) override;

      bool hasChildren() override;

      QObject* qObject() const;

   private:
      const QMetaObject* m_metaObject;
      QObject* m_objectvalue;
      static QColor s_backgroundColor;
      static QColor s_foregroundColor;
};

#endif // QOBJECTCLASSPROPERTYITEM_H