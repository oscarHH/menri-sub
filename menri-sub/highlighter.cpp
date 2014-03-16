#include <QtGui>
#include <QDebug>
#include "highlighter.h"

//! [0]
Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkMagenta);
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList keywordPatterns;
    keywordPatterns <<"[pP]age\\d[0-9]*" << "[pP]age\\d[0-9]*-[0-9]*"
                    <<"[pP]\\d[0-9]*"<<"[pP]\\d[0-9]*-[0-9]*"
                     <<" // " << "[a-zA-Z][^0-9]*\\:" ;

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

   // classFormat.setFontWeight(QFont::Bold);
    //classFormat.setForeground(Qt::darkMagenta);
    //evalua page(numeroPagina)
    //rule.pattern = QRegExp("\\page\\d[0-9]*" );
    //evalua p(numeroPagina)
    //rule.pattern = QRegExp("\\b[pP]\\d[0-9]*" );
    //rule.format = classFormat;
    //highlightingRules.append(rule);
    //! [2]
    //    classFormat.setFontWeight(QFont::Bold);
    //    classFormat.setForeground(Qt::darkMagenta);
    //    rule.pattern = QRegExp("\\bPage\\b" );
    //    rule.format = classFormat;
    //    highlightingRules.append(rule);
    //! [3]
    //comentarios
    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegExp("\\(.*s*\\)");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
    //multiLineCommentFormat.setForeground(Qt::red);

    //cajas de texto
    //variaslineas.setForeground(Qt::green);
    unalinea.setFontWeight(QFont::Bold);
    unalinea.setForeground(Qt::black);
    rule.pattern = QRegExp("\\[.*s*\\]");
    rule.format = unalinea;
    highlightingRules.append(rule);
    //variaslineas.setFontWeight(QFont::Bold);
    //variaslineas.setForeground(Qt::green);

    //! [3]

    //! [4]
    //quotationFormat.setForeground(Qt::darkGreen);
   // rule.pattern = QRegExp("\".*\"");
   // rule.format = quotationFormat;
  //  highlightingRules.append(rule);
    //! [4]

    //! [5]
    //functionFormat.setFontItalic(true);
    //functionFormat.setForeground(Qt::blue);
    //rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    //rule.format = functionFormat;
    //highlightingRules.append(rule);
    //! [5]

    //! [6]
    //comentarios
    //commentStartExpression = QRegExp("\\(");
    //commentEndExpression = QRegExp("\\)");
    //cajas
    //inicajatexto= QRegExp("\\[");
    //finalCajaTexto = QRegExp("\\]");
}
//! [6]

//! [7]
void Highlighter::highlightBlock(const QString &text)
{

    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

   /* int startIndex = 0;

    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    int inicioIndexc =0;
    if(previousBlockState() != 1)
        inicioIndexc = inicajatexto.indexIn(text);

    while (startIndex >= 0 || inicioIndexc >= 0) {

        if(inicioIndexc >= 0){
        int commentLength = 0;
        int finalindex = finalCajaTexto.indexIn(text,inicioIndexc);

        if(finalindex == -1){
            setCurrentBlockState(1);
            commentLength = text.length() - inicioIndexc;
        }else {
            commentLength = finalindex - inicioIndexc
                            + finalCajaTexto.matchedLength();
        }

        setFormat(inicioIndexc, commentLength, variaslineas);
        inicioIndexc =inicajatexto.indexIn(text, inicioIndexc + commentLength);

        }

        if(startIndex >= 0){
            int commentLength = 0;
            int endIndex = commentEndExpression.indexIn(text, startIndex);
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            } else {
                commentLength = endIndex - startIndex
                                + commentEndExpression.matchedLength();
            }
            setFormat(startIndex, commentLength, multiLineCommentFormat);
            startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
        }
    }*/


}

