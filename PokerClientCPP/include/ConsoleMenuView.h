#pragma once

/**
 * @file ConsoleMenuView.h
 * @brief File containing declaration of ConsoleMenuView class
 */

#include "IMenuView.h"
#include <string_view>

/**
 * @brief View for the console-based menu
 *
 * @details Implements the IMenuView interface to handle printing informations
 * via the standard console.
 * 
 */
class ConsoleMenuView : public IMenuView
{
public:
	/**
	 * @copydoc IMenuView::showMenuChoices()
	 *
	 */
	virtual void showMenuChoices() override;

	/**
	 * @copydoc IMenuView::showNicknameInput()
	 *
	 */
	virtual void showNicknameInput() override;

	/**
	 * @copydoc IMenuView::showIPInput()
	 *
	 */
	virtual void showIPInput() override;

	/**
	 * @copydoc IMenuView::showPortConnectInput()
	 *
	 */
	virtual void showPortConnectInput() override;

	/**
	 * @copydoc IMenuView::showPortCreateInput()
	 *
	 */
	virtual void showPortCreateInput() override;

	/**
	 * @copydoc IMenuView::showBotCountInput()
	 *
	 */
	virtual void showBotCountInput() override;

	/**
	 * @copydoc IMenuView::showPlayerCountInput()
	 *
	 */
	virtual void showPlayerCountInput() override;

	/**
	 * @copydoc IMenuView::showStartingChipsInput()
	 *
	 */
	virtual void showStartingChipsInput() override;

	/**
	 * @copydoc IMenuView::showError(std::string_view error)
	 *
	 */
	virtual void showError(std::string_view error) override;
};