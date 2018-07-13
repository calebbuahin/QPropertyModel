/*!
 * \author Caleb Amoa Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * \license
 * This file and its associated files, and libraries are free software.
 * You can redistribute it and/or modify it under the terms of the
 * Lesser GNU Lesser General Public License as published by the Free Software Foundation;
 * either version 3 of the License, or (at your option) any later version.
 * This file and its associated files is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.(see <http://www.gnu.org/licenses/> for details)
 * \copyright Copyright 2014-2018, Caleb Buahin, All rights reserved.
 * \date 2014-2018
 * \pre
 * \bug
 * \warning
 * \todo
 */

#include "stdafx.h"
#include <QFontDatabase>
#include "qcustomeditors.h"
#include "qfontfamilypropertyitem.h"
#include "qenumpropertyitem.h"
#include "qchildpropertyitems.h"


QSelectFromListPropertyItemEditor::QSelectFromListPropertyItemEditor(QWidget *parent)
   : QBasePropertyItemEditor(parent)
{

   m_fontFamily = QFontDatabase().families(QFontDatabase::WritingSystem::Any);
   m_comboBox = new QComboBox(this);
   m_comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   m_editorWidget = m_comboBox;
   static_cast<QHBoxLayout*>(layout())->insertWidget(0, m_comboBox);
   connect(m_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
}

QSelectFromListPropertyItemEditor::~QSelectFromListPropertyItemEditor()
{

}

void QSelectFromListPropertyItemEditor::setValue(const QVariant& value)
{
   switch (m_itemType)
   {
      case QBasePropertyItemEditor::Enum:
         for (int i = 0; i < m_metaEnum.keyCount(); i++)
         {
            if (value.toInt() == m_metaEnum.value(i))
            {
               m_comboBox->setCurrentIndex(i);
               break;
            }
         }
         break;
      case QBasePropertyItemEditor::Font:
         {
            int index = m_fontFamily.indexOf(value.toString());

            if (index > -1)
            {
               m_comboBox->setCurrentIndex(index);
            }
         }
         break;
      case QBasePropertyItemEditor::Unknown:
         break;
      default:
         break;
   }
}

QVariant QSelectFromListPropertyItemEditor::getValue() const
{
   switch (m_itemType)
   {
      case QBasePropertyItemEditor::Enum:
         return m_metaEnum.value(m_comboBox->currentIndex());
         break;
      case QBasePropertyItemEditor::Font:
         return m_comboBox->currentText();
         break;
      case QBasePropertyItemEditor::Unknown:
         break;
      default:
         break;
   }
   return QVariant();
}


void QSelectFromListPropertyItemEditor::setUpChildWidget()
{
   if (qobject_cast<QFontFamilyPropertyItem*>(m_propertyItem))
   {
      m_comboBox->clear();

      m_comboBox->addItems(m_fontFamily);

      for (int i = 0; i < m_fontFamily.count(); i++)
      {
         m_comboBox->setItemData(i, m_fontFamily[i], Qt::FontRole);
      }
      m_itemType = ItemType::Font;
   }
   else if (qobject_cast<QEnumPropertyItem*>(m_propertyItem))
   {
      QEnumPropertyItem* item = qobject_cast<QEnumPropertyItem*>(m_propertyItem);

      m_metaEnum = item->enumerator();

      m_comboBox->clear();

      for (int i = 0; i < m_metaEnum.keyCount(); i++)
      {
         m_comboBox->addItem(m_metaEnum.key(i));
      }

      m_itemType = ItemType::Enum;
   }
   else if (qobject_cast<QChildEnumPropertyItem*>(m_propertyItem))
   {
      QChildEnumPropertyItem* item = qobject_cast<QChildEnumPropertyItem*>(m_propertyItem);

      m_metaEnum = item->enumerator();

      m_comboBox->clear();

      for (int i = 0; i < m_metaEnum.keyCount(); i++)
      {
         m_comboBox->addItem(m_metaEnum.key(i));
      }

      m_itemType = ItemType::Enum;
   }
   else
   {
      m_itemType = ItemType::Unknown;

   }
}

void QSelectFromListPropertyItemEditor::onCurrentIndexChanged(int index)
{
   emit valueChanged(this);
}


