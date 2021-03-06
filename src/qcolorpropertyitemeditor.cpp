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
#include <QColorDialog>
#include "qcustomeditors.h"


QColorPropertyItemEditor::QColorPropertyItemEditor(QWidget *parent)
   : QPopUpPropertyItemEditor(parent)
{
   m_editorDialog = new QColorDialog(this);
   qobject_cast<QColorDialog*>(m_editorDialog)->setOption(QColorDialog::ShowAlphaChannel);
   m_valueProperty = qobject_cast<QColorDialog*>(m_editorDialog)->metaObject()->userProperty();
   connect(m_editorDialog, SIGNAL(accepted()), this, SLOT(onColorAccepted()));
   int pIndex = m_editorDialog->metaObject()->indexOfProperty("currentColor");
   m_valueProperty = m_editorDialog->metaObject()->property(pIndex);
}

QColorPropertyItemEditor::~QColorPropertyItemEditor()
{

}

void QColorPropertyItemEditor::setValue(const QVariant& value)
{
   if (value.canConvert<QColor>())
   {
      QColor c = qvariant_cast<QColor>(value);

      qobject_cast<QColorDialog*>(m_editorDialog)->setCurrentColor(c);
   }
}

void QColorPropertyItemEditor::onColorAccepted()
{
   emit valueChanged(this);
}
