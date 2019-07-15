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

#include "ActivityAnchorSettings.h"
#include "ActivityNetServiceTest.h"
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
ActivityAnchorSettings::ActivityAnchorSettings(	AppCommon& app,
												QWidget * parent )
: ActivityBase( "ActivityAnchorSettings", app, parent, eAppletMessenger, Qt::SubWindow )
{
	ui.setupUi(this);
	ui.m_TitleBarWidget->setTitleBarText( QObject::tr("Anchor Settings") );

	slotRepositionToParent();
	connectSignals();

	// save original values so can restore them if need be
	m_Engine.getEngineSettings().getAnchorWebsiteUrl( m_OrigAnchorUrl );
	m_Engine.getEngineSettings().getNetworkName( m_OrigNetworkName );
	m_Engine.getEngineSettings().getNetServiceWebsiteUrl( m_OrigConnectionTestUrl );

	updateDlgFromSettings();
}

//============================================================================
ActivityAnchorSettings::~ActivityAnchorSettings()
{
}

//============================================================================
void ActivityAnchorSettings::connectSignals( void )
{
	connect( ui.m_TitleBarWidget,				SIGNAL(signalBackButtonClicked()),				this, SLOT( slotHomeButtonClicked() ) );
	connect( ui.m_VerifySettingsButton,			SIGNAL(clicked()),								this, SLOT( onVerifySettingsButtonClick() ) );
	connect( ui.m_ManageSettingsButton,			SIGNAL(clicked()),								this, SLOT( onManageSettingsButtonClick() ) );
	connect( ui.m_AnchorSettingsNameComboBox,	SIGNAL(currentIndexChanged(const QString&)),	this, SLOT( onComboBoxSelectionChange(const QString&) ) );

	connect( ui.m_BeAnAnchorCheckBox,			SIGNAL(clicked()),								this, SLOT( onAttemptedSettingsChangeClick() ) );
	connect( ui.m_ConnectionTestUrlEdit,		SIGNAL(clicked()),								this, SLOT( onAttemptedSettingsChangeClick() ) );
	connect( ui.m_AnchorUrlEdit,				SIGNAL(clicked()),								this, SLOT( onAttemptedSettingsChangeClick() ) );
}

//============================================================================
void ActivityAnchorSettings::updateDlgFromSettings()
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
				selectedIdx			= currentSettingIdx;
				validDbSettings		= true;
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
		ui.m_ExcludeMeFromAnchorListCheckBox->setChecked( m_Engine.getEngineSettings().getExcludeMeFromAnchorList() );
	}
}

//============================================================================
void ActivityAnchorSettings::populateDlgFromAnchorSetting( AnchorSetting& anchorSetting )
{
	ui.m_AnchorUrlEdit->setText( anchorSetting.getAnchorWebsiteUrl().c_str() );
	ui.m_NetworkNameEdit->setText( anchorSetting.getNetworkName().c_str() );
	ui.m_ConnectionTestUrlEdit->setText( anchorSetting.getNetServiceWebsiteUrl().c_str() );
	ui.m_BeAnAnchorCheckBox->setChecked( anchorSetting.getIsThisNodeAnAnchor() );
	ui.m_ExcludeMeFromAnchorListCheckBox->setChecked( anchorSetting.getExcludeMeFromAnchorList() );
}

//============================================================================
void ActivityAnchorSettings::onComboBoxSelectionChange(const QString& anchorSettingName)
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
void ActivityAnchorSettings::updateSettingsFromDlg()
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
	anchorSetting.setIsThisNodeAnAnchor( ui.m_BeAnAnchorCheckBox->isChecked() );
	anchorSetting.setExcludeMeFromAnchorList( ui.m_ExcludeMeFromAnchorListCheckBox->isChecked() );
	m_MyApp.getDataHelper().updateAnchorSetting( anchorSetting );
	m_MyApp.getDataHelper().updateLastAnchorSettingName( anchorSettingsName.c_str() );
}

//============================================================================
void ActivityAnchorSettings::slotHomeButtonClicked()
{
	reject();
}

//============================================================================
void ActivityAnchorSettings::closeEvent( QCloseEvent * event )
{
	updateSettingsFromDlg();
	QDialog::closeEvent(event);
}

//============================================================================
void ActivityAnchorSettings::onVerifySettingsButtonClick( void )
{
	updateSettingsFromDlg();

	ActivityNetServiceTest * testDlg = new ActivityNetServiceTest( 
			m_MyApp,
			this			);
	testDlg->exec();
}

//============================================================================
void ActivityAnchorSettings::onAttemptedSettingsChangeClick( void )
{
	QMessageBox::warning(this, tr("Anchor Settings"), tr("You cannot edit setting here. Change settings in Manage Settings by clicking Manage Settings button" ) );
}

//============================================================================
void ActivityAnchorSettings::onManageSettingsButtonClick( void )
{
	updateSettingsFromDlg();

	ActivityManageAnchorSettings manageDlg( 
		m_MyApp,
		this			);
	manageDlg.exec();
	updateDlgFromSettings();
}
