/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN1VIEWBASE_HPP
#define SCREEN1VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class Screen1ViewBase : public touchgfx::View<Screen1Presenter>
{
public:
    Screen1ViewBase();
    virtual ~Screen1ViewBase();
    virtual void setupScreen();

    /*
     * Custom Actions
     */
    virtual void action1()
    {
        // Override and implement this function in Screen1
    }
    

    /*
     * Virtual Action Handlers
     */
    virtual void button1Clicked()
    {
        // Override and implement this function in Screen1
    }
    virtual void button2Clicked()
    {
        // Override and implement this function in Screen1
    }
    virtual void button3Clicked()
    {
        // Override and implement this function in Screen1
    }
    virtual void ButtonValidateClicked()
    {
        // Override and implement this function in Screen1
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image Background;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  Button1;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  Button2;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  Button3;
    touchgfx::Image ImageCode;
    touchgfx::TextArea textArea1;
    touchgfx::TextArea textArea2;
    touchgfx::TextArea textArea3;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  ButtonValidate;
    touchgfx::TextAreaWithOneWildcard textCode;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTCODE_SIZE = 100;
    touchgfx::Unicode::UnicodeChar textCodeBuffer[TEXTCODE_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen1ViewBase, const touchgfx::AbstractButtonContainer&> flexButtonCallback;

    /*
     * Callback Handler Declarations
     */
    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);

};

#endif // SCREEN1VIEWBASE_HPP
