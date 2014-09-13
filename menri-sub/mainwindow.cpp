#include "mainwindow.h"


QString version = " \t beta2 120914";
bool esGuardado = false;
int grados = 90;

//! [0] metodo constructor
MainWindow::MainWindow()
{
    abrir = new QFileDialog();
    guizip = new GuiZip();
    promocionLike = new like(this);
    config = new Configuraciones();
    archivotxt = new ManejoDearchivosTxt();
    posicion_ruta = 0;
    //creamos el editor
    codeEditor = new CodeEditor;
    codeEditor->setAcceptDrops(false);
    //resaltador de sintaxis
    highlighter = new Highlighter(codeEditor->document());
    //modelo para mostrar miniatura de imagenes
    m_imageView   = new ImagesView(this); //modelo
    m_imagesModel = new ImagesModel(this);//vista
    //objeto de tipo visorversion para poder mostrar las imagenes
    visor2 = new VisorVersion2;
    //asigna un modelo a la vista (miniatura de imagenes)
    m_imageView->setModel(m_imagesModel);
    
    InterfasGrafica (); //crea la interfas grafica
    AgregarAtajos (); //atajos del programa
    conexiones (); //conecta los componentes con la señal correspondiente
    comprobarConfiguraciones(); //comprueba la configuracion del programa
    leerCofiguracion(); //carga la configuracion
}



//implementacion del slot para mostrar u ocultar el panel imagenes
void MainWindow::panelImagen()
{
    if (imagenes->isChecked()) {
        DocArchivos->setVisible(true);
    } else {
        DocArchivos->setVisible(false);
    }
}

//slot  mostrar u ocultar el panel editor
void MainWindow::panelEditor()
{
    if (editor->isChecked()) {
        templateDocker->setVisible(true);
    } else {
        templateDocker->setVisible(false);
    }
}


//metodo para obtener la imagen
void MainWindow::obtenerImagen()
{
    listafileName = abrir->getOpenFileNames(this, tr("Seleccion de archivos"), QDir::homePath() + "/Pictures", tr("Image Files ( *.jpg *.png *.bmp *.psd *.svg *.psd *.jpeg *.gif *.txt"), 0 );
    
    //verificamos que la cadena no este vacia
    if (!listafileName.isEmpty()) {
        m_imagesModel->addImages(listafileName);
        if (m_imagesModel->tamanioLista() <= 0) {
            visor2->setRuta (listafileName.at (0));
        }
        updateActions();
    }
    listafileName.clear();
}

void MainWindow::open()
{
    if(codeEditor->document()->isModified() && !codeEditor->document()->isEmpty()){
        int opcion = guradarDatos();
        if(opcion == 1 ){
            GuardarTxt();
            archivoActual = "";
        }else if(opcion == 2){
            return;
        }else if(opcion == 3){
            obtenerImagen();
        }
    }else{
        obtenerImagen();
    }
}

//implementacion del slot zoom +
void MainWindow::zoomIn()
//! [9] //! [10]
{
    visor2->setTamanio (1.125);
    //zoom  = pw->f + 0.05f;
    //pasamos el valor del zoom
    // pw->setZoomFactor(zoom);
    //qDebug()<<zoom;
}

//implementacion del slot zoom -
void MainWindow::zoomOut()
{
    visor2->setTamanio (0.888889);
    
    /* zoom = pw->f - 0.05f;
    if (zoom <= 0.00968523) {
        zoom = 00.00968523f;
        //pasamos el valor del zoom
        pw->setZoomFactor(zoom);
    } else {
        //pasamos el valor del zoom
        pw->setZoomFactor(zoom);
    }*/
}

//implementacion del slot tamaño normal de la imagen
void MainWindow::normalSize()
{
    visor2->setTamanio (1.0);
}

//implementacion del slot acerca de menri-sub
void MainWindow::about()
{
    QMessageBox::about(this, tr("Acerca de Menri-sub"),
                       tr("<p><b>Menri-sub</b> Herramienta para ayudar a traducir manga, comics, etc."
                          "licencia GPL V3"
                          "</p>"
                          " by Oscar Hernandez Hernandez (H2O)"
                          ));
}

//metodo para la reacion de las opciones de la barra de menu
void MainWindow::createActions()
{
    //menu abrir
    openAct = new QAction(tr("&Abrir..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setIcon((QIcon(QPixmap(":/img/iconos/archivos.png"))));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    
    abrir_Proyecto = new QAction(tr("&Abrir Proyecto"),this);
    abrir_Proyecto->setShortcut(tr("alt+o"));
    abrir_Proyecto->setIcon((QIcon(QPixmap(":/img/iconos/archivos.png"))));
    connect(abrir_Proyecto,SIGNAL(triggered()),this,SLOT(abrirProyecto()));
    
    nuevo_Proyecto = new QAction(tr("&Nuevo Proyecto"),this);
    nuevo_Proyecto->setShortcut(tr("Ctrl+n"));
    nuevo_Proyecto->setIcon((QIcon(QPixmap(":/img/iconos/archivos.png"))));
    connect(nuevo_Proyecto,SIGNAL(triggered()),this,SLOT(nuevoProyecto()));
    
    guardar = new QAction(tr("&Guardar"),this);
    guardar->setShortcut(tr("Ctrl+S"));
    guardar->setIcon((QIcon(QPixmap(":/img/iconos/archivos.png"))));
    connect(guardar,SIGNAL(triggered()),this,SLOT(GuardarTxt()));
    
    guardarComo = new QAction(tr("&Guardar Como"),this);
    guardarComo->setShortcut(tr("Alt+S"));
    guardarComo->setIcon((QIcon(QPixmap(":/img/iconos/archivos.png"))));
    connect(guardarComo,SIGNAL(triggered()),this,SLOT(guardarCOmo()));
    
    exportar = new QAction(tr("&Exportar"), this);
    exportar->setShortcut(tr("Alt+e"));
    exportar->setIcon(QIcon(QPixmap(":/img/iconos/ayuda.png")));
    connect(exportar, SIGNAL(triggered()), this, SLOT(exportarTraduccion()));
    
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
    
    normalSizeAct = new QAction(tr("&Tamaño normal"), this);
    normalSizeAct->setShortcut(tr("Alt+N"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));
    
    pantallaCompleta = new QAction(tr("&Pantalla completa"), this);
    pantallaCompleta->setShortcut(tr("F11"));
    pantallaCompleta->setEnabled(true);
    pantallaCompleta->setCheckable(true);
    pantallaCompleta->setChecked(true);
    connect(pantallaCompleta, SIGNAL(triggered()), this, SLOT(fullpantalla()));
    
    anterior = new QAction(tr("anterior (<)"), this);
    anterior->setShortcut(Qt::CTRL +Qt::Key_Left);
    anterior->setEnabled(false);
    anterior->setIcon((QIcon(QPixmap(":/img/iconos/atras.png"))));
    connect(anterior, SIGNAL(triggered()), this, SLOT(anteriorImagen()));
    
    siguiente = new QAction(tr("siguiente (>)"), this);
    siguiente->setShortcut(Qt::CTRL + Qt::Key_Right);
    siguiente->setEnabled(false);
    siguiente->setIcon((QIcon(QPixmap(":/img/iconos/siguiente.png"))));
    connect(siguiente, SIGNAL(triggered()), this, SLOT(siguienteImagen()));
    
    limpiar = new QAction(tr("limpiar"), this);
    limpiar->setShortcut(tr("Ctrl+l"));
    limpiar->setEnabled(false);
    limpiar->setIcon((QIcon(QPixmap(":/img/iconos/limpiar.png"))));
    connect(limpiar, SIGNAL(triggered()), this, SLOT(limpiar_lista()));
    
    rotarImagenIzq = new QAction(tr("&Rotar Imagen izquierda"), this);
    rotarImagenIzq->setShortcut(tr("Ctrl+r"));
    rotarImagenIzq->setEnabled(false);
    connect(rotarImagenIzq, SIGNAL(triggered()), this, SLOT(RotarImagenIzquierda()));
    
    rotarImagenPersonalizado = new QAction(tr("&Rotar Imagen personalizado"), this);
    //rotarImagenIzq->setShortcut(tr("Ctrl+r"));
    rotarImagenPersonalizado->setEnabled(false);
    connect(rotarImagenPersonalizado, SIGNAL(triggered()), this, SLOT(RotarImagenPersonalizado()));
    
    rotarImagenDer = new QAction(tr("&Rotar Imagen derecha"), this);
    rotarImagenDer->setShortcut(tr("Ctrl+d"));
    rotarImagenDer->setEnabled(false);
    connect(rotarImagenDer, SIGNAL(triggered()), this, SLOT(RotarImagenDerecha()));
    
    imagenes = new QAction(tr("&Imagen"), this);
    imagenes->setCheckable(true);
    imagenes->setShortcut(tr("Ctrl+i"));
    imagenes->setChecked(true);
    connect(imagenes, SIGNAL(triggered()), this, SLOT(panelImagen()));
    
    editor = new QAction(tr("&Editor"), this);
    editor->setShortcut(tr("Ctrl+e"));
    editor->setCheckable(true);
    editor->setChecked(true);
    connect(editor, SIGNAL(triggered()), this, SLOT(panelEditor()));
    
    aboutAct = new QAction(tr("&Acerca de"), this);
    aboutAct->setIcon((QIcon(QPixmap(":/img/iconos/ayuda.png"))));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    
    siguenoslike = new QAction(tr("Visitanos"),this);
    siguenoslike->setIcon((QIcon(QPixmap(":/img/iconos/ayuda.png"))));
    connect(siguenoslike, SIGNAL(triggered()), this, SLOT(siguenos()));
    
    aboutQtAct = new QAction(tr("&Acerca de Qt"), this);
    aboutQtAct->setIcon((QIcon(QPixmap(":/img/iconos/ayuda.png"))));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    
    herramientascript = new QAction(tr("&Descomprimir"), this);
    herramientascript->setShortcut(tr("Ctrl+h"));
    herramientascript->setIcon(QIcon(QPixmap(":/img/iconos/ayuda.png")));
    connect(herramientascript, SIGNAL(triggered()), this, SLOT(listarScripts()));
    
    opciones = new QAction(tr("&Opciones"), this);
    opciones->setShortcut(tr("Alt+c"));
    opciones->setIcon(QIcon(QPixmap(":/img/iconos/ayuda.png")));
    connect(opciones, SIGNAL(triggered()), this, SLOT(configuraciones()));
    
    modoAjustePantalla = new QAction(tr("&Ajustar imagen en pantalla"), this);
    modoAjustePantalla->setShortcut(tr("ALT+i"));
    
    modolectura = new QAction(tr("&Modo lectura"), this);
    modolectura->setShortcut(tr("ALT+r"));
    modolectura->setCheckable(true);
    modolectura->setChecked(false);
    connect(modolectura, SIGNAL(triggered()), this, SLOT(lectura()));
}

//creamos y agregamos los menus a la barra de menu
void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&Archivo"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(abrir_Proyecto);
    fileMenu->addAction(nuevo_Proyecto);
    fileMenu->addAction(guardar);
    fileMenu->addAction(guardarComo);
    fileMenu->addSeparator();
    fileMenu->addAction(exportar);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    
    viewMenu = new QMenu(tr("&Ver"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addAction(pantallaCompleta);
    viewMenu->addAction( modolectura);
    
    viewMenu->addSeparator();
    viewMenu->addAction(anterior);
    viewMenu->addAction(siguiente);
    viewMenu->addAction(limpiar);
    viewMenu->addAction(rotarImagenIzq);
    viewMenu->addAction(rotarImagenDer);
    viewMenu->addAction(rotarImagenPersonalizado);
    
    helpMenu = new QMenu(tr("&Ayuda"), this);
    helpMenu->addAction(siguenoslike);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
    
    herramientas  = new QMenu(tr("&Herramientas"), this);
    herramientas->addAction(herramientascript);
    herramientas->addSeparator();
    herramientas->addAction(opciones);
    
    panel = viewMenu->addMenu(tr("&panel"));
    panel->addAction(imagenes);
    panel->addAction(editor);
    
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(herramientas);
    menuBar()->addMenu(helpMenu);
    
}

void MainWindow::leerCofiguracion()
{
    QSettings settings("menri-sub", "menri-sub");
    
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    color = qvariant_cast<QColor>(settings.value("color Fondo"));
    colorletra = qvariant_cast<QColor>(settings.value("color Texto"));
    QFont fondo = qvariant_cast<QFont>(settings.value("fuente beta"));
    bool primeravez = qvariant_cast<bool>(settings.value("primer inicio"));
    if(!primeravez){
        emit config->valorColor(Qt::black);
        emit config->valorColorFondo(Qt::white);
        emit config->valorFormatoLetra(QFont("Arial", 12));
        qDebug()<<"hola";
        return;
        
    }else{
        emit config->valorColor(colorletra);
        emit config->valorColorFondo(color);
        emit config->valorFormatoLetra(fondo);
        resize(size);
        move(pos);
    }
}

void MainWindow::RutaTxt(QString ruta)
{
    //archivoActual = ruta;
    archivotxt->setRutaArchivo(ruta);
    codeEditor->setPlainText(archivotxt->leerArchivo());
}

void MainWindow::GuardarTxt()
{
    
    esGuardado = false;
    QString fileName;
    
    if(archivoActual.isEmpty() && (!codeEditor->document()->isEmpty() || m_imagesModel->cantidad > 0)){
        fileName = QFileDialog::getSaveFileName(this, tr("Guardar"),QDir::homePath(),tr("menri(*.menri)"));
    }else if(codeEditor->document()->isEmpty() && m_imagesModel->cantidad < 0){
        return;
    }else {
        fileName = archivoActual;
    }
    
    if(!fileName.isNull()){
        
        QString res;
        res = fileName.replace(".menri","");
        
        QString ruta;
        
        archivotxt->setRutaArchivo(res +".mimg");
        if (archivotxt->archivoGuardar(m_imagesModel->rutaImagenes)){
            ruta += archivotxt->getRutaArchivos();
            
            archivotxt->setRutaArchivo(res+".mtxt");
            archivotxt->archivoGuardar(codeEditor->toPlainText());
            ruta +="\n"+ archivotxt->getRutaArchivos();
            
            archivotxt->setRutaArchivo(res+".menri");
            archivotxt->archivoGuardar(ruta);
            
            QMessageBox::information(
                        this,
                        tr("Guardar"),
                        tr("Se a guardado correctamente") );
            archivoActual = fileName;
            esGuardado = true;
            return;
        }else{
            QMessageBox::critical(
                        this,
                        tr("Guardar"),
                        tr("Ocurrio un error al guardar") );
            esGuardado = false;
            return;
            
        }
    }
}

void MainWindow::siguenos()
{
    promocionLike->exec();
}

void MainWindow::abrirProyecto()
{
    QString archivo = abrir->getOpenFileName(this, tr("Archivo de proyecto menri"), QDir::homePath(), tr("archivo menri ( *.menri)"), 0, QFileDialog::DontUseNativeDialog);
    if( !archivo.isEmpty()){
        limpiar_lista();
        codeEditor->setPlainText("");
        QStringList rutas; //almacena las rutas del proyecto
        QStringList imagenes; //almacena ruta de las imagenes
        archivoActual = archivo; //asigna el nombre del archivo abierto
        
        rutas = archivotxt->leerRutas(archivo); //lee el proyecto
        
        //lectura de imagenes
        imagenes = archivotxt->leerRutas(rutas.at(0));
        if (!imagenes.isEmpty()) {
            
            m_imagesModel->addImages(imagenes);
            if (m_imagesModel->tamanioLista() <= 0) {
                mandarImagen(imagenes.at(0));
            }
            updateActions();
        }
        //lectura de archivos
        RutaTxt(rutas.at(1));//obtiene el texto
        archivoActual = archivo;
        codeEditor->document()->setModified(false);
    }
}

void MainWindow::nuevoProyecto()
{
    if(codeEditor->document()->isModified() && !codeEditor->document()->isEmpty()){
        int opcion = guradarDatos();
        if(opcion == 1 ){
            GuardarTxt();
            archivoActual = "";
        }else if(opcion == 2){//cancelar
            return;
        }else if(opcion == 3){//descartar
            
            listafileName = abrir->getOpenFileNames(this, tr("Seleccion de archivos"), QDir::homePath() + "/Pictures", tr("Image Files ( *.jpg *.png *.bmp *.psd *.svg *.psd *.jpeg *.gif *.txt"), 0, QFileDialog::DontUseNativeDialog);
            
            //verificamos que la cadena no este vacia
            if (!listafileName.isEmpty()) {
                limpiar_lista();
                codeEditor->setPlainText("");
                m_imagesModel->addImages(listafileName);
                if (m_imagesModel->cantidad > 0) {
                    mandarImagen(listafileName.at(0));
                    updateActions();
                }
                listafileName.clear();
            }
            
            
        }
    }else{
        
        listafileName = abrir->getOpenFileNames(this, tr("Seleccion de archivos"), QDir::homePath() + "/Pictures", tr("Image Files ( *.jpg *.png *.bmp *.psd *.svg *.psd *.jpeg *.gif *.txt)"), 0, QFileDialog::DontUseNativeDialog);
        //verificamos que la cadena no este vacia
        if (!listafileName.isEmpty()) {
            limpiar_lista();
            codeEditor->setPlainText("");
            m_imagesModel->addImages(listafileName);
            if (m_imagesModel->cantidad > 0) {
                mandarImagen(listafileName.at(0));
                updateActions();
            }
            listafileName.clear();
        }
        
    }
    
    
}

void MainWindow::guardarCOmo()
{
    esGuardado = false;
    QString fileName;
    
    if(!codeEditor->document()->isEmpty() || m_imagesModel->cantidad >0){
        fileName = QFileDialog::getSaveFileName(this, tr("Guardar"),QDir::homePath(),tr("menri(*.menri)"));
    }
    
    if(!fileName.isNull()){
        
        
        fileName.remove(QRegularExpression(".menri"));
        QString ruta;
        
        archivotxt->setRutaArchivo(fileName +".mimg");
        if (archivotxt->archivoGuardar(m_imagesModel->rutaImagenes)){
            ruta += archivotxt->getRutaArchivos();
            
            archivotxt->setRutaArchivo(fileName+".mtxt");
            archivotxt->archivoGuardar(codeEditor->toPlainText());
            ruta +="\n"+ archivotxt->getRutaArchivos();
            
            archivotxt->setRutaArchivo(fileName+".menri");
            archivotxt->archivoGuardar(ruta);
            
            QMessageBox::information(
                        this,
                        tr("Guardar"),
                        tr("Se a guardado correctamente") );
            esGuardado = true;
            return;
        }else{
            QMessageBox::critical(
                        this,
                        tr("Guardar"),
                        tr("Ocurrio un error al guardar") );
            esGuardado = false;
            return;
            
        }
    }
    
}

void MainWindow::fullpantalla()
{
    if(pantallaCompleta->isChecked()){
        this->showFullScreen();
    }else{
        this->showMaximized();
    }
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
    codeEditor->installEventFilter(this);
    m_imageView->setEnabled(true);
    rotarImagenIzq->setEnabled(true);
    rotarImagenDer->setEnabled(true);
    rotarImagenPersonalizado->setEnabled(true);
}

//metodo que recibe la ruta de la imagen y la manda para poder mostrar
void MainWindow::mandarImagen(QString nombreImagen)
{
    if(!nombreImagen.endsWith(".txt")){
        visor2->setRuta (nombreImagen);
        QFileInfo info1;
        info1.setFile(nombreImagen);
        mStatLabel.setText("Nombre: "+info1.baseName());
    }
}



//reimplementacion de arrastrar y soltar elementos a la ventana
void MainWindow::dragEnterEvent(QDragEnterEvent  *event)
{
    event->acceptProposedAction();
}



//almacena las rutas de las imagenes
void MainWindow::dropEvent(QDropEvent * event)
{
    //variable de tipo archivo para obtener informacion.
    QFileInfo info1;
    //lista que  almacena la ruta de los archivos
    QStringList respaldo;
    
    lista = event->mimeData()->urls();
    
    QString fileName = "";
    //recorremos la lista
    for (int i = 0 ; i < lista.size(); i++) {
        //obtenemos la ruta del archivo
        fileName = lista.at(i).toLocalFile();
        //le pasamos la ruta del archivo a la variable info1 (QFileInfo)
        info1.setFile(fileName);
        //si alguien encuentra la forma de usar el event.mimedate().hasimage()
        //sera bienvenido al codigo xD
        
        //identifica archivos txt
        if(info1.completeSuffix().endsWith("txt")){
            //*********************++preguntar si desea guardar los cambios*****************************
            archivoActual = fileName;
            RutaTxt(fileName);
        }else /*por lo mientras usare esto para identificar que sea una imagen y almacenar en  lista*/if ((info1.completeSuffix().endsWith("jpg") || info1.completeSuffix().endsWith("png") || info1.completeSuffix().endsWith("jpeg") || info1.completeSuffix().endsWith("bmp") || info1.completeSuffix().endsWith("svg") || info1.completeSuffix().endsWith("psd") || info1.completeSuffix().endsWith("gif")))
        {
            //se agreaga la imagen a la lista
            respaldo.append(fileName);
            
        } else  if (info1.isDir()) /*si es una carpeta*/{
            //recorre la carpeta en busca de imagenes y las agrega a la lista y a la listwidget
            QDir carpeta(fileName);
            QString dato;
            foreach(QFileInfo direc, carpeta.entryInfoList()) {
                if (direc.isFile()) {
                    dato = direc.absoluteFilePath();
                    info1.setFile(dato);
                    if ((dato.endsWith(".jpg") || dato.endsWith(".png") || dato.endsWith(".jpeg") || dato.endsWith(".bmp") || dato.endsWith(".svg") || dato.endsWith(".psd") || dato.endsWith(".gif"))
                            && (info1.isFile() == true)) {
                        respaldo.append(dato);
                    }
                    
                }
            }
        }
    }
    if(respaldo.size() >0){
        m_imagesModel->addImages(respaldo);
        if (m_imagesModel->tamanioLista() <= 0) {
            mandarImagen(respaldo.at(0));
        }
    }
    
    respaldo.clear();
    updateActions();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (  codeEditor->document()->isModified() && !codeEditor->document()->isEmpty()) {
        int valorDelMensaje = guradarDatos();
        if (valorDelMensaje==1){
            GuardarTxt();
            if(esGuardado){
                event->accept();
            }else{
                event->ignore();
            }
            
        }else if(valorDelMensaje==2){
            event->ignore();
        }else if(valorDelMensaje==3){
            proceso.kill();
            event->accept();
        }
    }else{
        
        event->accept();
        proceso.kill();
        this->close();
    }
}

int MainWindow::guradarDatos()
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Menri-sub"),
                               tr("El documento a sido modificado.\n"
                                  "¿desea guardar los cambios?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save){
        return 1;
    }else if(ret == QMessageBox::Cancel){
        return 2;
    }else if(ret == QMessageBox::Discard){
        return 3;
    }
    return 0;
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

void MainWindow::obtenerIndex(const QModelIndex &index)
{
    posicion_ruta = index.row ();
}


void MainWindow::esImagenRemovida(const bool imagenRemovida)
{
    if(imagenRemovida == true){
        if(posicion_ruta  > m_imagesModel->tamanioLista ()-1) posicion_ruta -=1;
        if(m_imagesModel->tamanioLista () == 0 ){
            mandarImagen (":/img/iconos/portada.png");
            return;
        }
        
        
        QString Ruta = m_imagesModel->rutaImagen(posicion_ruta);
        //pasamos el nombre de la imagen
        mandarImagen(Ruta);
        updateActions();
    }
}



void MainWindow::siguienteImagen()
{
    if(m_imagesModel->tamanioLista() == 1){
        return;
        
    }
    
    if (posicion_ruta < m_imagesModel->tamanioLista()) {
        posicion_ruta++;
        btnSiguiente->setEnabled(true);
    }
    
    if (posicion_ruta < m_imagesModel->tamanioLista()) {
        QString sol = m_imagesModel->rutaImagen(posicion_ruta);
        //pasamos el nombre de la imagen
        mandarImagen(sol);
        updateActions();
    }
    
    if (posicion_ruta == m_imagesModel->tamanioLista()) {
        posicion_ruta = m_imagesModel->tamanioLista() - 1;
        btnSiguiente->setEnabled(false);
    }
    
}

void MainWindow::anteriorImagen()
{
    
    if(m_imagesModel->tamanioLista() == 1){
        return;
    }
    
    //comprobamos el tamaño de la lista
    if (m_imagesModel->tamanioLista() > 0) {
        posicion_ruta--;
        btnAnterior->setEnabled(true);
    }
    
    if (posicion_ruta >= 0) {
        QString sol = m_imagesModel->rutaImagen(posicion_ruta);
        //pasamos el nombre de la imagen
        mandarImagen(sol);
        updateActions();
    }
    
    //comprobamos que la variable posicion_ruta
    if (posicion_ruta <  0) {
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
    rotarImagenIzq->setEnabled(false);
    rotarImagenDer->setEnabled (false);
    rotarImagenPersonalizado->setEnabled(false);
    posicion_ruta =0;
    
}

void MainWindow::RotarImagenDerecha()
{
    visor2->setGrados (grados);
}

void MainWindow::RotarImagenIzquierda()
{
    visor2->setGrados (-grados);
}

void MainWindow::RotarImagenPersonalizado()
{
    
    bool ok;
    int  GradosPersonalizado = QInputDialog::getInt (this,tr("grados"),tr("Ingresa los grados a rotar"),grados,1,360,1,&ok);
    if(ok == true){
        grados = GradosPersonalizado;
        visor2->setGrados (grados);
    }
}

void MainWindow::listarScripts()
{
    
    /*qDebug()<<"hola";
    QStringList script;
    script <<"C:/Python27/ren.pyw";
    proceso.start("C:/Python27/pythonw.exe",script);*/
    //ListArchive("C:/Users/oscar/Documents/proyectos/build-pruebaunrar-Desktop_Qt_5_2_0_MSVC2010_32bit_OpenGL-Release/release/UnRDLL.rar");
    // m_imagesModel->removeAll(1,RutaImagenes.size()-1 );
    
    guizip->exec();
}

void MainWindow::configuraciones()
{
    config->cargarPalabras();
    config->exec();
}

void MainWindow::cambiarImagen(bool cambiar)
{
    if(cambiar){
        anteriorImagen();
    }else{
        siguienteImagen();
    }
    
}

void MainWindow::lectura(){
    
    if(modolectura->isChecked()){
        this->showFullScreen();
        menuBar()->setVisible(false);
        statusBar()->setVisible(false);
        DocArchivos->setVisible(false);
        templateDocker->setVisible(false);
        imagenes->setChecked(false);
        editor->setChecked(false);
        mainToolBar->setVisible(false);
        
        //if(!pantallaCompleta->isChecked()){pantallaCompleta->setChecked(true);}
    }else{
        DocArchivos->setVisible(true);
        statusBar()->setVisible(true);
        templateDocker->setVisible(true);
        menuBar()->setVisible(true);
        imagenes->setChecked(true);
        editor->setChecked(true);
        mainToolBar->setVisible(true);
    }
    
}

//agrega los atajos de teclado
void MainWindow::AgregarAtajos()
{
    this->addAction(openAct);
    this->addAction(modolectura);
    this->addAction(siguiente);
    this->addAction(anterior);
    this->addAction(zoomInAct);
    this->addAction(zoomOutAct);
    this->addAction(pantallaCompleta);
    this->addAction(rotarImagenIzq);
    this->addAction (rotarImagenDer);
    this->addAction (rotarImagenPersonalizado);
    this->addAction(limpiar);
}

//Agrega las conexiones
void MainWindow::conexiones()
{
    connect(m_imagesModel, SIGNAL(imageAdded()), this, SLOT(actionStatusSetter()));
    connect(m_imagesModel, SIGNAL(imageRemoved()), this, SLOT(actionStatusSetter()));
    connect(m_imageView, SIGNAL(clicked(QModelIndex)), this, SLOT(on_listWidget_clicked(QModelIndex)));
    connect(btnAnterior, SIGNAL(clicked()), this, SLOT(anteriorImagen()));
    connect(btnSiguiente, SIGNAL(clicked()), this, SLOT(siguienteImagen()));
    connect(btnLimpiar, SIGNAL(clicked()), this, SLOT(limpiar_lista()));
    connect (m_imageView,SIGNAL(cambiarImagen(bool)),this,SLOT(cambiarImagen(bool)));
    connect (m_imagesModel,SIGNAL(rutaTxt(QString)),this,SLOT(RutaTxt(QString)));
    connect(m_imageView, SIGNAL(pressed(QModelIndex)), this, SLOT(obtenerIndex(QModelIndex)));
    connect (m_imageView,SIGNAL(imagenRemovida(bool)),this,SLOT(esImagenRemovida(bool)));
    QObject::connect(config,SIGNAL(valorColor(QColor)),codeEditor,SLOT(otroColor(QColor)) );
    QObject::connect(config,SIGNAL(valorColorFondo(QColor)),codeEditor,SLOT(colorFondo(QColor)));
    QObject::connect(config,SIGNAL(valorFormatoLetra(QFont)),codeEditor,SLOT(otroFormatoLetra(QFont)) );    
}

void MainWindow::InterfasGrafica()
{
    /***********************Cracion de la interfas grafica*********************************/
    //contenedor
    QWidget * w = new QWidget;
    //layout verticcal
    QVBoxLayout * mainLayout = new  QVBoxLayout(w);
    //layout horizontal
    QHBoxLayout * buttonLayout = new QHBoxLayout;
    
    //creamos el panel flotante del editor
    templateDocker = new QDockWidget;
    //creamos el panel flotante de la lista de imagenes
    DocArchivos = new QDockWidget;
    
    //creo botones para cambiar de imagenes y limpiar la lista
    btnAnterior = new QPushButton;
    btnSiguiente = new QPushButton;
    btnLimpiar = new QPushButton;
    btnSiguiente->setIcon(QIcon(QPixmap(":/img/iconos/siguiente.png")));
    btnAnterior->setIcon(QIcon(QPixmap(":/img/iconos/atras.png")));
    btnLimpiar->setIcon(QIcon(QPixmap(":/img/iconos/limpiar.png")));
    btnAnterior->setEnabled(false);
    btnSiguiente->setEnabled(false);
    btnLimpiar->setEnabled(false);
    
    mainLayout->addWidget(m_imageView);
    buttonLayout->addWidget(btnAnterior);
    buttonLayout->addWidget(btnLimpiar);
    buttonLayout->addWidget(btnSiguiente);
    mainLayout->addLayout(buttonLayout);
    
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
    templateDocker->setVisible(true);
    setCentralWidget(visor2);
    
    //creamos acciones
    createActions();
    //se crea los menus
    createMenus();
    //titulo de la ventana
    setWindowTitle(tr("Menri-sub  ") + version);
    
    //menu
    mainToolBar = addToolBar(tr("Main Toolbar"));
    mainToolBar->addAction(anterior);
    mainToolBar->addAction(limpiar);
    mainToolBar->addAction(siguiente);
    mainToolBar->addAction(zoomInAct);
    mainToolBar->addAction(zoomOutAct);
    //toolBarArea();
    addToolBar(Qt::BottomToolBarArea, mainToolBar);
    
    //barra de estado
    //mStatLabel = new QLabel;
    //mStatLabel2 = new QLabel;
    //mStatLabel->setText("hola mundo");
    //mStatLabel2->setText("que tal");
    mStatLabel.setText("");
    statusBar()->addPermanentWidget(&mStatLabel2);
    statusBar()->addPermanentWidget(&mStatLabel);
    setAcceptDrops(true);
    visor2->setAcceptDrops (false);
    
}


void MainWindow::exportarTraduccion(){
    
    if(codeEditor->document()->isEmpty()){
        return;
    }
    
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Exportar traduccion"),QDir::homePath(),tr("txt(*.txt)"));
    
    
    if(!fileName.isNull()){
        archivotxt->setRutaArchivo (fileName);
        if (archivotxt->archivoGuardar(codeEditor->toPlainText ())){
            
            QMessageBox::information(
                        this,
                        tr("Exportar"),
                        tr("Se a exportado correctamente") );
            return;
        }else{
            QMessageBox::critical(
                        this,
                        tr("Guardar"),
                        tr("Ocurrio un error al guardar") );
            return;
            
        }
    }
}


void MainWindow::comprobarConfiguraciones()
{
    QDir ruta(QDir::homePath()+"/.menri-sub");
    
    //--------verifica todas las carpetas existan de lo contrario se crean----------
    if(!ruta.mkdir(QDir::homePath()+"/.menri-sub")){
        qDebug()<<"ocurrio un error1";
    }
    
    if(!ruta.mkdir(QDir::homePath()+"/.menri-sub/config")){
        qDebug()<<"ocurrio un error 2";
    }
    
    if(!ruta.mkdir(QDir::homePath()+"/.menri-sub/comandos")){
        qDebug()<<"ocurrio un error 3";
    }
    
    if(!ruta.mkdir(QDir::homePath()+"/.menri-sub/temas")){
        qDebug()<<"ocurrio un error 4";
    }
    
    //-------comprueba que los archivos existan de lo contrariose crean------
    QFile archivo(QDir::homePath()+"/.menri-sub/config/recortes.mconfig");
    
    if(!archivo.exists()){//archivo de recortes
        QString pal = "page,rgb,etiqueta\nhola,mkv,palabra"; //datos por default
        archivotxt->setRutaArchivo(archivo.fileName());
        archivotxt->archivoGuardar(pal);
    }
    
}
