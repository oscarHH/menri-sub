
#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>



//! [0]
class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;

    //cajas cajas de texto
    //QRegExp inicajatexto;
    //QRegExp finalCajaTexto;
    QTextCharFormat unalinea;
    //QTextCharFormat variaslineas;


    //comentarios de traduccion
    //QRegExp commentStartExpression;
    //QRegExp commentEndExpression;
    //esta en una linea
    QTextCharFormat singleLineCommentFormat;
    //varias lineas
    //QTextCharFormat multiLineCommentFormat;

    //QTextCharFormat quotationFormat;
    //QTextCharFormat functionFormat;
};
//! [0]

#endif
