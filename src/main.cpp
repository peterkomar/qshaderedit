
#include "qshaderedit.h"
#include "nofocusstyle.h"

#include <QtGui/QApplication>


int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(qshaderedit);
	
    QApplication app(argc, argv);
    app.setStyle(new NoFocusStyle);

    QString filename;
    if (qApp->arguments().size() > 1) {
	    filename = qApp->arguments().at(1);
    }
   
    QShaderEdit shaderEdit(filename);
    shaderEdit.show();

    return app.exec();
}
