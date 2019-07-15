//============================================================================
// Copyright (C) 2013 Brett R. Jones
// Issued to MIT style license by Brett R. Jones in 2017
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// bjones.engineer@gmail.com
// http://www.gotvptop.com
//============================================================================

#include "ActivityManageAnchorSettings.h"
#include "AppCommon.h"
#include "AppGlobals.h"
#include "VxDataHelper.h"

#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettings.h>
#include <GoTvCore/GoTvP2P/P2PEngine/EngineSettingsDefaultValues.h>
#include <NetLib/VxGetRandomPort.h>
#include <NetLib/AnchorSetting.h>

#include <QMessageBox>

//============================================================================
ActivityManageAnchorSettings::ActivityManageAnchorSettings(	AppCommon& app, QWidget * parent )
: ActivityBase(  "ActivityManageAnchorSettings", app, parent, eAppletMessenger, Qt::SubWindow )
, m_MyApp( app )
{
	ui.setupUi(this);
	ui.m_TitleBarWidget->setTitleBarText( QObject::tr("Manage Anchor Settings") );

	slotRepositionToParent();
	updateDlgFromSettings();
	connectSignals();
}

//============================================================================
ActivityManageAnchorSettings::~ActivityManageAnchorSettings()
{
}

//============================================================================
void ActivityManageAnchorSettings::connectSignals( void )
{
	connect( ui.m_TitleBarWidget,					SIGNAL(signalBackButtonClicked()),				this, SLOT(slotHomeButtonClicked()) );
	connect( ui.m_SaveSettingsButton,				SIGNAL(clicked()),								this, SLOT( onSaveButtonClick()) );
	connect( ui.m_DeleteSettingsButton,				SIGNAL(clicked()),								this, SLOT( onDeleteButtonClick()) );
	connect( ui.m_BeAnAnchorCheckBox,				SIGNAL(clicked()),								this, SLOT( onBeAnAnchorCheckBoxClick()) );
	connect( ui.m_ExcludeMeFromAnchorListCheckBox,	SIGNAL(clicked()),								this, SLOT( onExcludeMeFromAnchorListCheckBoxClick()) );
	connect( ui.m_AnchorSettingsNameComboBox,		SIGNAL(currentIndexChanged(const QString&)),	this, SLOT( onComboBoxSelectionChange(const QString&)) );
	connect( ui.m_AnchorSettingsNameComboBox,		SIGNAL(editTextChanged(const QString&)),		this, SLOT( onComboBoxTextChanged(const QString&)) );
}

//============================================================================
void ActivityManageAnchorSettings::onComboBoxTextChanged ( const QString & text )
{
	//updateSettingsFromDlg();
}

//============================================================================
void ActivityManageAnchorSettings::onComboBoxSelectionChange(const QString& anchorSettingName)
{
	VxDataHelper& dataHelper = m_MyApp.getDataHelper();
	AnchorSetting anchorSetting;
	if( dataHelper.getAnchorSettingByName( anchorSettingName.toUtf8(), anchorSetting ) )
	{
		populateDlgFromAnchorSetting( anchorSetting );
		updateSettingsFromDlg();
	}
}

//============================================================================
void ActivityManageAnchorSettings::populateDlgFromAnchorSetting( AnchorSetting& anchorSetting )
{
	ui.m_AnchorUrlEdit->setText( anchorSetting.getAnchorWebsiteUrl().c_str() );
	ui.m_NetworkNameEdit->setText( anchorSetting.getNetworkName().c_str() );
	ui.m_ConnectionTestUrlEdit->setText( anchorSetting.getNetServiceWebsiteUrl().c_str() );
	ui.m_BeAnAnchorCheckBox->setChecked( anchorSetting.getIsThisNodeAnAnchor() );
	ui.m_ExcludeMeFromAnchorListCheckBox->setChecked( anchorSetting.getExcludeMeFromAnchorList() );
}

//============================================================================
void ActivityManageAnchorSettings::updateDlgFromSettings()
{
	ui.m_AnchorSettingsNameComboBox->clear();

	bool validDbSettings = false;
	VxDataHelper& dataHelper = m_MyApp.getDataHelper();
	std::vector<AnchorSetting> anchorSettingList;
	std::string lastSettingsName = dataHelper.getLastAnchorSettingName();
	int selectedIdx = 0;
	int currentSettingIdx = 0;
	if( ( 0 != lastSettingsName.length() )
		&& dataHelper.getAllAnchorSettings( anchorSettingList )
		&& ( 0 != anchorSettingList.size() ) )
	{
		std::vector<AnchorSetting>::iterator iter;
		for( iter = anchorSettingList.begin(); iter != anchorSettingList.end(); ++iter )
		{
			AnchorSetting& anchorSetting = *iter;
			ui.m_AnchorSettingsNameComboBox->addItem( anchorSetting.getAnchorSettingName().c_str() );
			if( anchorSetting.getAnchorSettingName() == lastSettingsName )
			{
				// found last settings used
				selectedIdx = currentSettingIdx;
				validDbSettings = true;
				populateDlgFromAnchorSetting( anchorSetting );
			}

			currentSettingIdx++;
		}
	}

	if( validDbSettings )
	{
		ui.m_AnchorSettingsNameComboBox->setCurrentIndex( selectedIdx );
	}
	else if( anchorSettingList.size() )
	{
		ui.m_AnchorSettingsNameComboBox->addItem( anchorSettingList[0].getAnchorSettingName().c_str() );
		populateDlgFromAnchorSetting( anchorSettingList[0] );
		dataHelper.updateLastAnchorSettingName( anchorSettingList[0].getAnchorSettingName().c_str() );
	}
	else
	{
		ui.m_AnchorSettingsNameComboBox->addItem( "default" );
		std::string strValue;

		m_Engine.getEngineSettings().getAnchorWebsiteUrl( strValue );
		ui.m_AnchorUrlEdit->setText( strValue.c_str() );

		m_Engine.getEngineSettings().getNetworkName( strValue );
		ui.m_NetworkNameEdit->setText( strValue.c_str() );

		m_Engine.getEngineSettings().getNetServiceWebsiteUrl( strValue );
		ui.m_ConnectionTestUrlEdit->setText( strValue.c_str() );

		ui.m_BeAnAnchorCheckBox->setChecked( m_Engine.getEngineSettings().getIsThisNodeAnAnchor() );
		ui.m_ExcludeMeFromAnchorListCheckBox->setChecked(  false );
	}
}

//============================================================================
void ActivityManageAnchorSettings::updateSettingsFromDlg()
{
	AnchorSetting anchorSetting;
	std::string anchorSettingsName;
    anchorSettingsName = ui.m_AnchorSettingsNameComboBox->currentText().toUtf8().constData();
	if( 0 == anchorSettingsName.length() )
	{
		anchorSettingsName = "default";
	}

	anchorSetting.setAnchorSettingName( anchorSettingsName.c_str() );

	std::string strValue;
    strValue = ui.m_AnchorUrlEdit->text().toUtf8().constData();
	m_Engine.getEngineSettings().setAnchorWebsiteUrl( strValue );
	anchorSetting.setAnchorWebsiteUrl( strValue.c_str() );

    strValue = ui.m_NetworkNameEdit->text().toUtf8().constData();
	m_Engine.getEngineSettings().setNetworkName( strValue );
	anchorSetting.setNetworkName( strValue.c_str() );

    strValue = ui.m_ConnectionTestUrlEdit->text().toUtf8().constData();
	m_Engine.getEngineSettings().setNetServiceWebsiteUrl( strValue );
	anchorSetting.setNetServiceWebsiteUrl( strValue.c_str() );

	m_Engine.getEngineSettings().setIsThisNodeAnAnchor( ui.m_BeAnAnchorCheckBox->isChecked() );
	m_Engine.getEngineSettings().setExcludeMeFromAnchorList( ui.m_ExcludeMeFromAnchorListCheckBox->isChecked() );
	anchorSetting.setIsThisNodeAnAnchor( ui.m_BeAnAnchorCheckBox->isChecked() );
	anchorSetting.setExcludeMeFromAnchorList( ui.m_ExcludeMeFromAnchorListCheckBox->isChecked() );
	m_MyApp.getDataHelper().updateAnchorSetting( anchorSetting );
	m_MyApp.getDataHelper().updateLastAnchorSettingName( anchorSettingsName.c_str() );
}

//============================================================================
void ActivityManageAnchorSettings::slotHomeButtonClicked()
{
	reject();
}

//============================================================================
void ActivityManageAnchorSettings::closeEvent( QCloseEvent * event )
{
	updateSettingsFromDlg();
	QDialog::closeEvent(event);
}

//============================================================================
void ActivityManageAnchorSettings::onSaveButtonClick( void )
{
	updateSettingsFromDlg();
	QMessageBox::information(this, tr("Anchor Setting"), tr("Anchor setting was saved." ) );
}

//============================================================================
void ActivityManageAnchorSettings::onDeleteButtonClick( void )
{
	updateSettingsFromDlg();
	if( 1 >= ui.m_AnchorSettingsNameComboBox->count() )
	{
		QMessageBox::warning(this, tr("Anchor Settings"), tr("You cannot delete the last anchor setting." ) );
		return;
	}

	std::string anchorSettingsName;
    anchorSettingsName = ui.m_AnchorSettingsNameComboBox->currentText().toUtf8().constData();
	if( 0 != anchorSettingsName.length() )
	{
		m_MyApp.getDataHelper().removeAnchorSettingByName( anchorSettingsName.c_str() );
		updateDlgFromSettings();
	}
}

//============================================================================
void ActivityManageAnchorSettings::onBeAnAnchorCheckBoxClick( void )
{
	updateSettingsFromDlg();
}

//============================================================================
void ActivityManageAnchorSettings::onExcludeMeFromAnchorListCheckBoxClick( void )
{
	updateSettingsFromDlg();
}
