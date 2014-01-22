#include <QtWidgets>
#include <QFileSystemModel>
#include <QTreeView>
#include "mainwindow.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QToolButton>
#include <QMimeData>
#include <QtPlugin>
#include <QPluginLoader>
#include <QProcess>

//variables
float su ;
QString version = " \t alfa-0.2   18/01/14";
bool activoPanelEditor = false;
bool activoPanelImagen = true;
int grados = 0;

QStringList listafileName;
QProcess proceso;

//! [0] construccion de la ventana
MainWindow::MainWindow()
{
    guizip = new GuiZip();
    //contenedor
    QWidget * w = new QWidget;
    //layout verticcal
    QVBoxLayout * mainLayout = new  QVBoxLayout(w);
    //layout horizontal
    QHBoxLayout * buttonLayout = new QHBoxLayout;

    posicion_ruta=0;
    //creamos el editor
    codeEditor = new CodeEditor;
    //resalta la sintaxis
    highlighter = new Highlighter(codeEditor->document());
    //coloco el icono a la ventanaprincipal
    //creo una lista para almacenar las imagenes

    //view = new QListWidget;
    m_imageView   = new ImagesView( this );
    m_imagesModel = new ImagesModel( this );
    m_imageView->setModel( m_imagesModel );
    connect( m_imagesModel, SIGNAL( imageAdded()   ), this, SLOT( actionStatusSetter() ) );
    connect( m_imagesModel, SIGNAL( imageRemoved() ), this, SLOT( actionStatusSetter() ) );

    //creo botones para cambiar de imagenes y limpiar la lista
    btnAnterior = new QPushButton;
    btnSiguiente = new QPushButton;
    btnLimpiar =new QPushButton;
    btnSiguiente->setIcon(QIcon(QPixmap(":/img/iconos/siguiente.png")));
    btnAnterior->setIcon(QIcon(QPixmap(":/img/iconos/atras.png")));
    btnLimpiar->setIcon(QIcon(QPixmap(":/img/iconos/limpiar.png")));
    btnAnterior->setEnabled(false);
    btnSiguiente->setEnabled(false);
    btnLimpiar->setEnabled(false);
    mainLayout->addWidget(m_imageView );
    buttonLayout->addWidget(btnAnterior);
    buttonLayout->addWidget(btnLimpiar);
    buttonLayout->addWidget(btnSiguiente);
    mainLayout->addLayout(buttonLayout);

    //cuando la imagen es de mayor tamaño se le  coloca una barra de desplazamiento
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setEnabled(false);
    //creamos el panel flotante del editor
    templateDocker = new QDockWidget;
    //creamos el panel flotante de la lista de imagenes
    DocArchivos = new QDockWidget;
    //le decimos en que lugares se puede acomodar
    templateDocker->setAllowedAreas(Qt::AllDockWidgetAreas);
    DocArchivos->setAllowedAreas(Qt::AllDockWidgetAreas);
    templateDocker->setObjectName("Editor");
    DocArchivos->setObjectName("Imagenes");
    //le agregamos titulo a la ventana flotante
    templateDocker->setWindowTitle(tr("Editor"));
    DocArchivos->setWindowTitle(tr("Imagenes"));
    //le decimos en que posicion debe de estar los paneles
    templateDocker->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
    DocArchivos->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
    //agregamos la ventana flotantes
    addDockWidget(Qt::BottomDockWidgetArea, templateDocker);
    addDockWidget(Qt::LeftDockWidgetArea, DocArchivos);
    //agregamos el contenido de los paneles
    templateDocker->setWidget(codeEditor);
    DocArchivos->setWidget(w);
    //agregamos en el are de en medio
    setCentralWidget(scrollArea);
    //creamos acciones
    createActions();
    //se crea los menus
    createMenus();
    //titulo de la ventana
    setWindowTitle(tr("Menri-sub  ")+ version);
    mandarImagen(":/img/iconos/portada.png");

    templateDocker->setVisible(false);
    //menu
    QToolBar * mainToolBar = addToolBar(tr("Main Toolbar"));
    mainToolBar->addAction(anterior);
    mainToolBar->addAction(limpiar);
    mainToolBar->addAction(siguiente);
    mainToolBar->addAction(zoomInAct);
    mainToolBar->addAction(zoomOutAct);
    //toolBarArea();
    addToolBar(Qt::RightToolBarArea,mainToolBar);
    //barra de estado
    QLabel *mStatLabel = new QLabel;
    QLabel *mStatLabel2 = new QLabel;
    mStatLabel->setText("hola mundo");
    mStatLabel2->setText("que tal");
    statusBar()->addPermanentWidget(mStatLabel2);
    statusBar()->addPermanentWidget(mStatLabel);
    setAcceptDrops(true);
    //tamaño de la ventana
    //el programa inicia maximizado
    setWindowState(Qt::WindowMaximized );
    //conectamos
    connect(m_imageView, SIGNAL( clicked(QModelIndex)),this,SLOT(on_listWidget_clicked(QModelIndex)));
    connect(btnAnterior,SIGNAL(clicked()),this,SLOT(anteriorImagen()));
    connect(btnSiguiente,SIGNAL(clicked()),this,SLOT(siguienteImagen()));
    connect(btnLimpiar,SIGNAL(clicked()),this,SLOT(limpiar_lista()));
    abrir = new QFileDialog();

}


//implementacion del slot para mostrar u ocultar el panel imagenes
void MainWindow::panelImagen()
{
    if(activoPanelImagen == true){
        DocArchivos->setVisible(false);
        activoPanelImagen= false;
    }else{
        DocArchivos->setVisible(true);
        activoPanelImagen= true;
    }
}


//implementacion del slot para mostrar u ocultar el panel editor
void MainWindow::panelEditor()
{

    if(activoPanelEditor == false){
        templateDocker->setVisible(true);
        activoPanelEditor = true;
    }else{
        templateDocker->setVisible(false);
        activoPanelEditor= false;
    }

}


//metodo para obtener la imagen
void MainWindow::obtenerImagen()
{

    listafileName = abrir->getOpenFileNames(this, tr("Open Image"), QDir::homePath()+"/Pictures", tr("Image Files ( *.jpg *.png *.bmp *.psd *.svg *.psd "),0, QFileDialog::DontUseNativeDialog );

    //verificamos que la cadena no este vacia
    if (!listafileName.isEmpty()) {
        m_imagesModel->addImages(listafileName);
        if(m_imagesModel->tamanioLista() <= 0){
            mandarImagen(listafileName.at(0));
        }
        updateActions();
    }
    listafileName.clear();
}



void MainWindow::open()
{
    //color = QColorDialog::getColor(Qt::green, this);
    obtenerImagen();
}

//implementacion del slot zoom +
void MainWindow::zoomIn()
//! [9] //! [10]
{
    zoom  = pw->f + 0.05f;
    //pasamos el valor del zoom
    pw->setZoomFactor(zoom);
}

//implementacion del slot zoom -
void MainWindow::zoomOut()
{
    zoom = pw->f - 0.05f;
    if( zoom <= 0.00968523   ){
        zoom = 00.00968523f;
        //pasamos el valor del zoom
        pw->setZoomFactor(zoom);
    }else{
        //pasamos el valor del zoom
        pw->setZoomFactor(zoom);
    }
}

//implementacion del slot tamaño normal de la imagen
void MainWindow::normalSize()
{
    zoom = 0.3f;
    pw->setZoomFactor(zoom);
}

//implementacion del slot acerca de menri-sub
void MainWindow::about()
{
    QMessageBox::about(this, tr("Acerca de Menri-sub"),
                       tr("<p><b>Menri-sub</b> Herramienta para ayudar a traducir manga, comics, etc. "
                          "</p>"));
}


//metodo para la reacion de las opciones de la barra de menu
void MainWindow::createActions()
{
    //menu abrir
    openAct = new QAction(tr("&Abrir..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    //colocamos un icono al menu
    openAct->setIcon((QIcon(QPixmap(":/img/iconos/archivos.png"))));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("&Salir"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    zoomInAct = new QAction(tr("Zoom (+)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    zoomInAct->setIcon((QIcon(QPixmap(":/img/iconos/zoom+.png"))));
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("Zoom (-)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    zoomOutAct->setIcon((QIcon(QPixmap(":/img/iconos/zoom-.png"))));
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    anterior = new QAction(tr("anterior (<)"), this);
    anterior->setShortcut(Qt::Key_Left);
    anterior->setEnabled(false);
    anterior->setIcon((QIcon(QPixmap(":/img/iconos/atras.png"))));
    connect(anterior, SIGNAL(triggered()), this, SLOT(anteriorImagen()));

    siguiente = new QAction(tr("siguiente (>)"), this);
    siguiente->setShortcut(Qt::Key_Right);
    siguiente->setEnabled(false);
    siguiente->setIcon((QIcon(QPixmap(":/img/iconos/siguiente.png"))));
    connect(siguiente, SIGNAL(triggered()), this, SLOT(siguienteImagen()));

    limpiar = new QAction(tr("limpiar"), this);
    limpiar->setShortcut(tr("Ctrl+l"));
    limpiar->setEnabled(false);
    limpiar->setIcon((QIcon(QPixmap(":/img/iconos/limpiar.png"))));
    connect(limpiar, SIGNAL(triggered()), this, SLOT(limpiar_lista()));


    normalSizeAct = new QAction(tr("&Tamaño normal"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));


    rotarImagen = new QAction(tr("&Rotar Imagen"), this);
    rotarImagen->setShortcut(tr("Ctrl+r"));
    rotarImagen->setEnabled(false);
    connect(rotarImagen, SIGNAL(triggered()), this, SLOT(RotarImagen()));


    imagenes = new QAction(tr("&Imagen"),this);
    imagenes->setCheckable(true);
    imagenes->setShortcut(tr("Ctrl+i"));
    imagenes->setChecked(true);
    connect(imagenes, SIGNAL(triggered()), this, SLOT(panelImagen()));

    editor = new QAction(tr("&Editor"),this);
    editor->setShortcut(tr("Ctrl+e"));
    editor->setCheckable(true);
    editor->setChecked(false);
    connect(editor, SIGNAL(triggered()), this, SLOT(panelEditor()));

    aboutAct = new QAction(tr("&Acerca de"), this);
    aboutAct->setIcon((QIcon(QPixmap(":/img/iconos/ayuda.png"))));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("&Acerca de Qt"), this);
    aboutQtAct->setIcon((QIcon(QPixmap(":/img/iconos/ayuda.png"))));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    herramientascript = new QAction(tr("&Descomprimir"),this);
    herramientascript->setShortcut(tr("Ctrl+h"));
    herramientascript->setIcon(QIcon(QPixmap(":/img/iconos/ayuda.png")));
    connect(herramientascript, SIGNAL(triggered()),this, SLOT(listarScripts()));


}

//creamos y agregamos los menus a la barra de menu
void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&Archivo"), this);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = new QMenu(tr("&Ver"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(anterior);
    viewMenu->addAction(siguiente);
    viewMenu->addAction(limpiar);
    viewMenu->addAction(rotarImagen);
    helpMenu = new QMenu(tr("&Ayuda"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    herramientas  = new QMenu(tr("&Herramientas"),this);
    herramientas->addAction(herramientascript);

    panel = viewMenu->addMenu(tr("&panel"));
    panel->addAction(imagenes);
    panel->addAction(editor);



    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(herramientas);
    menuBar()->addMenu(helpMenu);


}

//actualizamos el estado de los menus
void MainWindow::updateActions()
{
    zoomInAct->setEnabled(true);
    zoomOutAct->setEnabled(true);
    normalSizeAct->setEnabled(true);
    anterior->setEnabled(true);
    siguiente->setEnabled(true);
    btnAnterior->setEnabled(true);
    btnSiguiente->setEnabled(true);
    btnLimpiar->setEnabled(true);
    limpiar->setEnabled(true);
    //view->installEventFilter(this);
    m_imageView->installEventFilter(this);
    //view->setEnabled(true);
    m_imageView->setEnabled(true);
    scrollArea->setEnabled(true);
    rotarImagen->setEnabled(true);
}

//metodo que recibe la ruta de la imagen y la manda para poder mostrar
void MainWindow::mandarImagen(QString nombreImagen)
{
    grados =0;
    pw = new PixmapWidget( nombreImagen,  scrollArea );
    //asigamos que se pueda redimensionar
    scrollArea->setWidgetResizable(true);
    //el scrollArea contiene a pw y dibuja la imagen
    scrollArea->setWidget(pw);
}



//reimplementacion de arrastrar y soltar elementos a la ventana
void MainWindow::dragEnterEvent (QDragEnterEvent  *event){
    event->acceptProposedAction();

}

void	MainWindow::dragLeaveEvent(QDragLeaveEvent * event){

    event->accept();
}

void	MainWindow::dragMoveEvent(QDragMoveEvent * event){
    event->accept();
}

//almacena las rutas de las imagenes
void MainWindow::dropEvent(QDropEvent * event){

    //QIcon nuevo;
    grados =0;
    //variable de tipo archivo para obtener informacion.
    QFileInfo info1;
    //lista que  almacena la ruta de los archivos
    QStringList respaldo;

    lista = event->mimeData()->urls();
    QString fileName="";


    //recorremos la lista
    for(int i=0 ; i < lista.size();i++){
        //obtenemos la ruta del archivo
        fileName=lista.at(i).toLocalFile();
        //si la ruta contiene % se elimina el numero 25 que aparece
       // qDebug()<<fileName;
        //le pasamos la ruta del archivo a la variable info1 (QFileInfo)
        info1.setFile(fileName);
        //si alguien encuentra la forma de usar el event.mimedate().hasimage()
        //sera bienvenido al codigo xD

        //por lo mientras usare esto para identificar que sea una imagen y almacenar en  lista
        if(  (info1.completeSuffix().endsWith("jpg") || info1.completeSuffix().endsWith("png") || info1.completeSuffix().endsWith("jpeg") ||info1.completeSuffix().endsWith("bmp") ||info1.completeSuffix().endsWith("svg") ||info1.completeSuffix().endsWith("psd") )
             ){
            //se agreaga la imagen a la lista
            respaldo.append(fileName);

            //si es una carpeta
        }else  if(info1.isDir()){
            //{recorre la carpeta en busca de imagenes y las agrega a la lista y a la listwidget}
            QDir carpeta (fileName);
            QString dato;
            foreach (QFileInfo direc,carpeta.entryInfoList()) {
                if(direc.isFile()){
                    dato = direc.absoluteFilePath();
                    info1.setFile(dato);
                    if(  (dato.endsWith(".jpg") || dato.endsWith(".png") ||dato.endsWith(".jpeg") ||dato.endsWith(".bmp") ||dato.endsWith(".svg") || dato.endsWith(".psd")  )
                         && (info1.isFile() == true)){
                        respaldo.append(dato);
                    }

                }
            }
        }
    }
    m_imagesModel->addImages(respaldo);
    if(m_imagesModel->tamanioLista() <= 0){
        mandarImagen(respaldo.at(0));
    }
    respaldo.clear();
    updateActions();
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    m_imagesModel->stopAddImages();
    proceso.kill();
    this->close();
    event->accept();
}

//para la obtener la posicion de cada elemnto del  listwidget
void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{ 
    //obtenemos el valor de la listwidget
    posicion_ruta = index.row();
    //obtenemos el valor y lo convertimos a texto
    QString Ruta = m_imagesModel->rutaImagen(posicion_ruta);
    //pasamos el nombre de la imagen
    mandarImagen(Ruta);
    updateActions();
}



void MainWindow::siguienteImagen()
{
    grados =0;
    if(posicion_ruta < m_imagesModel->tamanioLista()){
        posicion_ruta++;
        btnSiguiente->setEnabled(true);
    }

    if(posicion_ruta < m_imagesModel->tamanioLista()){
        QString sol = m_imagesModel->rutaImagen(posicion_ruta);
        //pasamos el nombre de la imagen
        mandarImagen(sol);
        updateActions();
    }

    if(posicion_ruta == m_imagesModel->tamanioLista()){
        posicion_ruta=m_imagesModel->tamanioLista()-1;
        btnSiguiente->setEnabled(false);
    }


}

void MainWindow::anteriorImagen()
{
    grados =0;
    //comprobamos el tamaño de la lista
    if(m_imagesModel->tamanioLista() > 0){
        posicion_ruta--;
        btnAnterior->setEnabled(true);
    }

    if(posicion_ruta >= 0){
        QString sol = m_imagesModel->rutaImagen(posicion_ruta);
        //pasamos el nombre de la imagen
        mandarImagen(sol);
        updateActions();
    }

    //comprobamos que la variable posicion_ruta
    if(posicion_ruta <  0){
        posicion_ruta = 0;
        btnAnterior->setEnabled(false);
    }
}

void MainWindow::limpiar_lista()
{
    //limpia el listwidget
    m_imagesModel->removeAll();
    mandarImagen(":/img/iconos/portada.png");
    zoomInAct->setEnabled(false);
    zoomOutAct->setEnabled(false);
    normalSizeAct->setEnabled(false);
    anterior->setEnabled(false);
    siguiente->setEnabled(false);
    btnAnterior->setEnabled(false);
    btnSiguiente->setEnabled(false);
    btnLimpiar->setEnabled(false);
    limpiar->setEnabled(false);
    m_imageView->setEnabled(false);
    scrollArea->setEnabled(false);
    rotarImagen->setEnabled(false);
}

void MainWindow::RotarImagen()
{
    grados +=90;

    if(grados > 360){
        grados = 90;
    }

    pw->setGrados(grados);
    pw->repaint();
}

void MainWindow::listarScripts()
{
    /*qDebug()<<"hola";
    QStringList script;
    script <<"C:/Python27/ren.pyw";
    proceso.start("C:/Python27/pythonw.exe",script);*/
    //ListArchive("C:/Users/oscar/Documents/proyectos/build-pruebaunrar-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Release/release/UnRDLL.rar");
    // m_imagesModel->removeAll(1,RutaImagenes.size()-1 );
    guizip->show();
}


//metodo para los eventos
bool MainWindow::eventFilter(QObject * watched, QEvent * e)
{
    if (watched == m_imageView && e->type() == QEvent::KeyPress) {
        QKeyEvent * ke = static_cast<QKeyEvent * >(e);

        if (ke->key() == Qt::Key_Up ) {
            anteriorImagen();
            return true;
        }else if(ke->key() == Qt::Key_Down){
            siguienteImagen();
            return true;
        }
    }
    return QWidget::eventFilter(watched, e);
}
