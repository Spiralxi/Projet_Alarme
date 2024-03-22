#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <string> // Assurez-vous d'inclure la bibliothèque de chaîne de caractères.

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void button1Clicked();
    virtual void button2Clicked();
    virtual void button3Clicked();
    virtual void ButtonValidateClicked();

protected:

    std::string userInput; // Pour stocker les entrées de l'utilisateur.
    std::string secretCode; // Le code secret à comparer.
    static constexpr size_t LOG_BUFFER_SIZE = 256; // Définir selon le besoin
    char logBuffer[LOG_BUFFER_SIZE];
    void updateTextCode();
    void displayValidationResult(bool isValid);
};

#endif // SCREEN1VIEW_HPP
