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
//#include "visor/PixmapWidget.h"
#include <QImageIOPlugin>
#include "configuracion/configuraciones.h"
#include "editor/manejodearchivostxt.h"
#include "promocion/like.h"
#include <visor/visorversion2.h>

QT_BEGIN_NAMESPACE
//class PixmapWidget;
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
class ManejoDearchivosTxt;
class VisorVersion2;
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

    QLabel mStatLabel ;
    QLabel mStatLabel2 ;

    void updateActions();
    QFileDialog *abrir;
    ImagesModel *m_imagesModel;
    void mandarImagen(QString  nombreImagen);
    QString archivoActual;
     bool eventFilter(QObject * watched, QEvent * e);

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
    void obtenerIndex(const QModelIndex &index);
    void esImagenRemovida(const bool);
    void siguienteImagen();
    void anteriorImagen();
    void limpiar_lista();
    void RotarImagen();
    void listarScripts();
    void configuraciones();
    void cambiarImagen(bool tev);
    void RutaTxt(QString ruta);
    void GuardarTxt();
    void siguenos();
    void abrirProyecto();
    void nuevoProyecto();
    void guardarCOmo();
    void fullpantalla();
    void lectura();
    void exportarTraduccion();
    void comprobarConfiguraciones();
    //void moverbarrasDesplazadoras(int x,int y);
    //void slotAjustarImagenPantalla();
    

private:
    ManejoDearchivosTxt * archivotxt;
    void createActions();
    void createMenus();

    //void scaleImage(double factor);
    //void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QAction   *m_addImages;
    bool       m_stopImageAdd;

    QDockWidget * templateDocker;
    QDockWidget * DocArchivos;
    GuiZip * guizip;
    like * promocionLike;
    Configuraciones * config;
    CodeEditor *codeEditor;
    Highlighter *highlighter;


    ImagesView  *m_imageView;

    void leerCofiguracion();

    int guradarDatos();
protected:
    virtual  void dragEnterEvent(QDragEnterEvent * event);
    virtual  void dragLeaveEvent(QDragLeaveEvent * event);
    virtual  void dragMoveEvent(QDragMoveEvent * event);
    virtual  void dropEvent(QDropEvent * event);
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    
    QToolBar * mainToolBar;
    QAction *openAct;
    QAction *abrir_Proyecto;
    QAction *nuevo_Proyecto;

    QAction *guardar;
    QAction *guardarComo;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *siguiente;
    QAction *anterior;
    QAction *limpiar;
    QAction *normalSizeAct;
    QAction *pantallaCompleta;
    QAction *rotarImagen;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *imagenes;
    QAction *editor;
    QAction *herramientascript;
    QAction *opciones;
    QAction *siguenoslike;
    QAction * modolectura;
    QAction * modoAjustePantalla;
    QAction * exportar;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QMenu *panel;
    QMenu *herramientas;
    
    // QColor color;
    //QScrollArea *scrollArea;
    VisorVersion2 * v2;
    //PixmapWidget *pw;

    QPushButton *btnSiguiente;
    QPushButton *btnAnterior;
    QPushButton *btnLimpiar;

    float zoom;
    QList<QUrl> lista;
    QImage *qImg;    
    
};
//![0]

#endif // MAINWINDOW_H
