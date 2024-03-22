#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/utils.hpp>
#include <string>

Screen1View::Screen1View()
: secretCode("123")
{
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::button1Clicked(){
    userInput += "1";
    updateTextCode();
}

void Screen1View::button2Clicked(){
    userInput += "2";
    updateTextCode();
}

void Screen1View::button3Clicked(){
    userInput += "3";
    updateTextCode();
}

void Screen1View::updateTextCode() {
    touchgfx::Unicode::UnicodeChar tmp[150];
    Unicode::strncpy(tmp, userInput.c_str(), 150);
    Unicode::snprintf(textCodeBuffer, 150, tmp);
    textCode.invalidate();
}

void Screen1View::ButtonValidateClicked(){
    if(userInput == secretCode) {
        touchgfx_printf("Code correct\n");
        displayValidationResult(true); // Affiche "Code correct"
    } else {
        touchgfx_printf("Code incorrect\n");
        displayValidationResult(false); // Affiche "Code incorrect"
    }
    userInput.clear(); // Efface la saisie de l'utilisateur après la vérification
}

void Screen1View::displayValidationResult(bool isValid) {
    touchgfx::Unicode::UnicodeChar tmp[150];
    if(isValid) {
        Unicode::strncpy(tmp, "Code correct", 150);
    } else {
        Unicode::strncpy(tmp, "Code incorrect", 150);
    }
    Unicode::snprintf(textCodeBuffer, 150, tmp);
    textCode.invalidate(); // Force le widget à se rafraîchir
}
