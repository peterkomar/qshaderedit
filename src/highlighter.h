
#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QtGui/QSyntaxHighlighter>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtGui/QTextCharFormat>


class Highlighter: public QSyntaxHighlighter
{
	Q_OBJECT

public:
	enum FormatType {
		Keyword = 0,
		Comment,
		DataType,
		BuiltinVar,
		BuiltinFunction,
		Number,
		String,
		Misc,
		FormatType_Max
	};

	struct Rule
	{
		QRegExp pattern;
		FormatType type;
	};

        friend FormatType& operator ++(FormatType& f){
            int k = (int)f;
            ++k;
            f = (FormatType)k;
            return f; }

    //Highlighter(QTextDocument* parent);
        Highlighter(QObject *parent=0);

	void setRules(const QList<Rule>& rules);
	void setMultiLineCommentStart(const QString& s);
	void setMultiLineCommentEnd(const QString& s);

        static void createFormats();

        /*****************************Peter Komar code, august 2009 ***************************/
        static  QTextCharFormat readSettings(FormatType type);
        static void writeSettings(FormatType type, const QTextCharFormat& format);
        static QFont readFontSettings();
        static void saveFontSettings(const QFont& font);
        static QString getSyntaxKeyWords(const QString& extation, const char* type);
        static QStringList getKeyWords(const QString& extation);
       /********************************************************************************/


protected:
	void highlightBlock(const QString& text);

private:
	QList<Rule> m_rules;
	QString m_multiLineCommentStart;
	QString m_multiLineCommentEnd;

	static QVector<QTextCharFormat> s_formats; // idx is FormatType
};

#endif
