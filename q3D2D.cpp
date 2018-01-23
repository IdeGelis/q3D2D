//##########################################################################
//#                                                                        #
//#                       CLOUDCOMPARE PLUGIN: q3D2D                       #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#                             COPYRIGHT: ENSG Iris de Gelis              #
//#                                                                        #
//##########################################################################

//System
#include <iostream>
#include <typeinfo>

//Qt
#include <QtGui>
#include <QMainWindow>
#include <QString>

//3D2D
#include "q3D2D.h"
#include "q3D2Ddlg.h"

//qCC
#include "ccGLWindow.h"
#include "ccPickingHub.h"

//Default constructor: should mainly be used to initialize
//actions (pointers) and other members
q3D2D::q3D2D(QObject* parent/*=0*/)
	: QObject(parent)
	, m_action(0)
{
}

//This method should enable or disable each plugin action
//depending on the currently selected entities ('selectedEntities').
//For example: if none of the selected entities is a cloud, and your
//plugin deals only with clouds, call 'm_action->setEnabled(false)'
void q3D2D::onNewSelection(const ccHObject::Container& selectedEntities)
{
	//if (m_action)
	//	m_action->setEnabled(!selectedEntities.empty());
}

//This method returns all 'actions' of your plugin.
//It will be called only once, when plugin is loaded.
void q3D2D::getActions(QActionGroup& group)
{
	//default action (if it has not been already created, it's the moment to do it)
	if (!m_action)
	{
		//here we use the default plugin name, description and icon,
		//but each action can have its own!
		m_action = new QAction(getName(),this);
		m_action->setToolTip(getDescription());
		m_action->setIcon(getIcon());
		//connect appropriate signal
		connect(m_action, SIGNAL(triggered()), this, SLOT(doAction()));
	}

	group.addAction(m_action);
}

//This is an example of an action's slot called when the corresponding action
//is triggered (i.e. the corresponding icon or menu entry is clicked in CC's
//main interface). You can access to most of CC components (database,
//3D views, console, etc.) via the 'm_app' attribute (ccMainAppInterface
//object).
void q3D2D::doAction()
{
	//m_app should have already been initialized by CC when plugin is loaded!
	//(--> pure internal check)
	assert(m_app);
	if (!m_app)
		return;

	/*** HERE STARTS THE ACTION ***/
    std::cout<<"Initialisation of q3D2D Plugin"<<std::endl;
    //show dialog to let the user choose the operation to perform
    //q3D2DDlg dlg(m_app->getMainWindow());

    ccGLWindow* win = m_app->getActiveGLWindow();
    m_app->dispToConsole("[q3D2D] Ouverture de q3D2D!",ccMainAppInterface::STD_CONSOLE_MESSAGE);

    if (win){
        q3D2DDlg* dlg = new q3D2DDlg();
        dlg->win = win;
        dlg->m_app = m_app;
        dlg->show();
    }






	//This is how you can output messages
       // m_app->dispToConsole("[q3D2D] Hello world!",ccMainAppInterface::STD_CONSOLE_MESSAGE); //a standard message is displayed in the console
       // m_app->dispToConsole("[q3D2D] Warning: My plugin shouldn't be used as is!",ccMainAppInterface::WRN_CONSOLE_MESSAGE); //a warning message is displayed in the console
       // m_app->dispToConsole("Hello!!!! =)",ccMainAppInterface::ERR_CONSOLE_MESSAGE); //an error message is displayed in the console AND an error box will pop-up!

	/*** HERE ENDS THE ACTION ***/

}

//This method should return the plugin icon (it will be used mainly
//if your plugin as several actions in which case CC will create a
//dedicated sub-menu entry with this icon.
QIcon q3D2D::getIcon() const
{
        //open q3D2D.qrc (text file), update the "prefix" and the
	//icon(s) filename(s). Then save it with the right name (yourPlugin.qrc).
        //(eventually, remove the original q3D2D.qrc file!)
        return QIcon(":/CC/plugin/q3D2D/icon.png");
}
