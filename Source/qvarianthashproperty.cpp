#include "stdafx.h"
#include "qvarianthashproperty.h"

QVariantHashProperty::QVariantHashProperty(const QVariantHash& value, const QMetaProperty& metaProperty,QtPropertyModel* const &  model,int row, QVariantProperty *parent)
	: QVariantProperty(value, metaProperty,model, row ,parent)
{

}

QVariantHashProperty::~QVariantHashProperty()
{

}

QVariant QVariantHashProperty::getData(Qt::ItemDataRole role , Column column)
{
	switch (column)
	{
	case QVariantProperty::PropertyNameColumn:
		switch (role)
		{
		case Qt::DecorationRole:
			return QVariant();
			break;
		case Qt::EditRole:
			return QVariant();
			break;
		case Qt::DisplayRole:
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
			{
				return propertyName;
			}
			break;
		case Qt::FontRole:
			return QVariant();
			break;
		case Qt::TextAlignmentRole:
			return QVariant();
			break;
		case Qt::BackgroundRole:
			return QVariant();
			break;
		case Qt::ForegroundRole:
			return QVariant();
			break;
		case Qt::CheckStateRole:
			return QVariant();
			break;
		case Qt::AccessibleTextRole:
			return QVariant();
			break;
		case Qt::AccessibleDescriptionRole:
			return QVariant();
			break;
		case Qt::SizeHintRole:
			return QVariant();
			break;
		case Qt::InitialSortOrderRole:
			return QVariant();
			break;
		}

		break;
	case QVariantProperty::PropertyValueColumn:
		switch (role)
		{
		case Qt::DecorationRole:
			return QVariant();
			break;
		case Qt::EditRole:
			return value;
			break;
		case Qt::DisplayRole:
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
			{
				QVariantHash temp = qvariant_cast<QVariantHash>(value);
				return "[Count = " +QString::number(temp.count())+"]";
			}
			break;
		case Qt::FontRole:
			return QVariant();
			break;
		case Qt::TextAlignmentRole:
			return QVariant();
			break;
		case Qt::BackgroundRole:
			return QVariant();
			break;
		case Qt::ForegroundRole:
			return QVariant();
			break;
		case Qt::CheckStateRole:
			return QVariant();
			break;
		case Qt::AccessibleTextRole:
			return QVariant();
			break;
		case Qt::AccessibleDescriptionRole:
			return QVariant();
			break;
		case Qt::SizeHintRole:
			return QVariant();
			break;
		case Qt::InitialSortOrderRole:
			return QVariant();
			break;
		}
		break;
	}
	return QVariant();
}

Qt::ItemFlags QVariantHashProperty::flags() const
{
	Qt::ItemFlags flags = Qt::ItemIsSelectable| Qt::ItemIsEnabled | Qt::ItemIsEditable  ;

	//if(metaProperty.isValid()) 
	//{
	//	if(metaProperty.isWritable())
	//		flags = flags;
	//}
	//else
	//{
	//	if(defaultFlags.testFlag(Qt::ItemIsEditable))
	//	{
	//		return Qt::ItemIsSelectable | Qt::ItemIsEnabled  | Qt::ItemIsEditable;
	//	}
	//	else
	//	{
	//	   return flags  ;
	//	}
	//}

	return flags;
}