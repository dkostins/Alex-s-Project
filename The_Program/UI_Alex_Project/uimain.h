#ifndef UIMAIN_H
#define UIMAIN_H

#include <string>
#include <QMainWindow>
#include <QString>
namespace Ui {
class UiMain;
}

class UiMain : public QMainWindow
{
    Q_OBJECT
private:
    std::string Input="0000";
    Ui::UiMain *ui;
public:
    QString fileName;
    void loadFromFile();
    std::string checkClicked();
    void parseClicks(std::string formatting);
    QString getFont();
    QString getFontSize();

    explicit UiMain(QWidget *parent = 0);
    std::string getString(){
        return Input;
    }
    void setString(std::string input){
        Input = input;
    }

    ~UiMain();
private slots:
    void openWord();
     void saveToFile();


};


#endif // UIMAIN_H
