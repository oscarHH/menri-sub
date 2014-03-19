#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QFileInfo>
#include <QLabel>
#include <QFileDialog>
#include "herramientas/ManejoComprimido/guizip.h"
#include "visor/imagesmodel.h"
#include "visor/imagesview.h"
#include "editor/codeeditor.h"
#include "editor/highlighter.h"
#include "visor/PixmapWidget.h"
#include <QImageIOPlugin>
#include "configuracion/configuraciones.h"

QT_BEGIN_NAMESPACE
class PixmapWidget;
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QDockWidget;
class CodeEditor;
class QEvent;
class GuiZip;
class ImagesView;
class ImagesModel;
class QSettings;
//class Configuraciones;
QT_END_NAMESPACE

//![0]
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:


    MainWindow();
    ~MainWindow();
    //QPixmap *icon_to_be_shown;
    int posicion_ruta;
    void mandarImagen(QString  nombreImagen);
    QLabel mStatLabel ;
    QLabel mStatLabel2 ;

    void updateActions();
    QFileDialog *abrir;
    ImagesModel *m_imagesModel;

public slots:
    void panelImagen();
    void panelEditor();
    void open();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void about();
    void obtenerImagen();
    void on_listWidget_clicked(const QModelIndex &index);

    void siguienteImagen();
    void anteriorImagen();
    void limpiar_lista();
    void RotarImagen();
    void listarScripts();
    void configuraciones();
    void cambiarImagen(bool tev);
signals:
    //void	itemClicked(QListWidgetItem * item);
    //metodos a implementar
private:

    void createActions();
    void createMenus();

    //void scaleImage(double factor);
    //void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QAction   *m_addImages;
    bool       m_stopImageAdd;

    QDockWidget * templateDocker;
    QDockWidget * DocArchivos;
    GuiZip * guizip;
    Configuraciones * config;
    CodeEditor *codeEditor;
    Highlighter *highlighter;


    ImagesView  *m_imageView;

protected:
    virtual  void dragEnterEvent(QDragEnterEvent * event);
    virtual  void dragLeaveEvent(QDragLeaveEvent * event);
    virtual  void dragMoveEvent(QDragMoveEvent * event);
    virtual  void dropEvent(QDropEvent * event);
    void closeEvent(QCloseEvent *event);

    QAction *openAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *siguiente;
    QAction *anterior;
    QAction *limpiar;
    QAction *normalSizeAct;
    QAction *rotarImagen;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *imagenes;
    QAction *editor;
    QAction *herramientascript;
    QAction *opciones;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QMenu *panel;
    QMenu *herramientas;
    // QColor color;
    QScrollArea *scrollArea;

    PixmapWidget *pw;

    QPushButton *btnSiguiente;
    QPushButton *btnAnterior;
    QPushButton *btnLimpiar;

    float zoom;
    QList<QUrl> lista;
    QImage *qImg;

};
//![0]

#endif // MAINWINDOW_H
