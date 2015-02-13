#include "stdafx.h"
#include "qrectfpropertyitem.h"
#include "qpropertymodel.h"

QRectFPropertyItem::QRectFPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent)
	: QVariantPropertyItem(value, metaProperty, parent), m_isSettingChildren(false)
{

}

QRectFPropertyItem::~QRectFPropertyItem()
{

}

QVariant QRectFPropertyItem::data(int column, Qt::ItemDataRole  role) const
{

	switch (column)
	{
	case QPropertyItem::Property:
		switch (role)
		{
		case Qt::DisplayRole:
			return m_name;
			break;
		}

		break;
	case QPropertyItem::Value:
		switch (role)
		{
		case Qt::EditRole:
		{
			return  m_metaProperty.read(m_parent->qObject());

		}break;
		case Qt::DisplayRole:
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
		{
			QRectF v = qvariant_cast<QRectF>(m_metaProperty.read(m_parent->qObject()));
			QString label = QString("[X=%1, Y=%2, Width=%3, Height=%4]").arg(v.x()).arg(v.y()).arg(v.width()).arg(v.height());
			return label;
		}
		break;
		}

		break;
	}
	return QVariant();
}


void QRectFPropertyItem::setChildValues()
{
	if (!m_isSettingChildren)
	{
		m_isSettingChildren = true;

		QRectF v = qvariant_cast<QRectF>(m_metaProperty.read(m_parent->qObject()));

		for (int i = 0; i < m_children.count(); i++)
		{
			QPropertyItem* child = m_children[i];
			QString propertyName = child->name();
			QVariant tval;

			if (propertyName == "X")
			{
				tval = v.x();
			}
			else if (propertyName == "Y")
			{
				tval = v.y();
			}
			else if (propertyName == "Width")
			{
				tval = v.width();
			}
			else if (propertyName == "Height")
			{
				tval = v.height();
			}
			m_model->setData(child->index(), tval);
		}


		m_isSettingChildren = false;
	}
}

bool QRectFPropertyItem::hasChildren()
{
	if (!m_childrenSet)
	{
		m_childrenSet = true;

		QRectF v = qvariant_cast<QRectF>(m_metaProperty.read(m_parent->qObject()));

		QPropertyItem* X = new QPropertyItem(v.x(), "X", this);
		m_children.append(X);
		connect(X, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
			SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

		QPropertyItem* Y = new QPropertyItem(v.y(), "Y", this);
		m_children.append(Y);
		connect(Y, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
			SLOT(onChildItemValueChanged(const QString&, const QVariant&)));


		QPropertyItem* width = new QPropertyItem(v.width(), "Width", this);
		m_children.append(width);
		connect(width, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
			SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

		QPropertyItem* height = new QPropertyItem(v.height(), "Height", this);
		m_children.append(height);

		connect(height, SIGNAL(valueChanged(const QString&, const QVariant&)), this,
			SLOT(onChildItemValueChanged(const QString&, const QVariant&)));

		return true;
	}
	else
	{
		if (m_children.count() > 0)
		{
			return true;
		}
	}

	return false;
}

Qt::ItemFlags QRectFPropertyItem::flags() const
{
	Qt::ItemFlags  flags;

	if (m_isCheckable)
		flags = flags | Qt::ItemFlag::ItemIsUserCheckable;
	if (m_isEnabled)
		flags = flags | Qt::ItemFlag::ItemIsEnabled;
	//if (m_isEditable)
	//	flags = flags | Qt::ItemFlag::ItemIsEditable;
	if (m_isEnabled)
		flags = flags | Qt::ItemFlag::ItemIsEnabled;
	if (m_isSelectable)
		flags = flags | Qt::ItemFlag::ItemIsSelectable;
	if (m_isTristate)
		flags = flags | Qt::ItemFlag::ItemIsTristate;

	return flags;
}

void QRectFPropertyItem::onChildItemValueChanged(const QString& name, const QVariant& value)
{
	if (!m_isSettingChildren)
	{
		m_isSettingChildren = true;

		QRectF v = qvariant_cast<QRectF>(m_metaProperty.read(m_parent->qObject()));

		if (name == "X")
		{
			v.setX(value.toDouble());
		}
		else if (name == "Y")
		{
			v.setY(value.toDouble());
		}
		else if (name == "Width")
		{
			v.setWidth(value.toDouble());
		}
		else if (name == "Height")
		{
			v.setHeight(value.toDouble());
		}

		m_model->setData(m_index, v);

		m_isSettingChildren = false;

	}
}