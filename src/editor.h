#ifndef EDITOR_H
#define EDITOR_H

#include <QtGui/QToolBox>
#include <QtGui/QTextDocument>
#include <QtGui/QPlainTextEdit>


class Effect;
class Highlighter;
class SourceEdit;
class Completer;

class Editor : public QToolBox
{
	Q_OBJECT
public:
	
	Editor(QWidget * parent = 0);
	
	void setEffect(Effect * effect);
	
        QPlainTextEdit * addEditor(const QString & name, const Effect * effect, int i);
        QPlainTextEdit * currentTextEdit() const;

	int line() const;
	int column() const;

	bool isModified() const;
	void setModified(bool b);

        /************************Peter Komar code, august 2009 ***********************/
        void updateHighlighter();
        /***************************************************************/

	
public slots:
	void undo();
	void redo();
	void cut();
	void copy();
	void paste();

	void gotoLine(int tab, int line, int column = 0);
	void nextTab();
	void previousTab();

	void findDialog();
	void gotoDialog();
	void findNext();
	void findPrevious();
	
signals:
	void cursorPositionChanged();
	void copyAvailable(bool available);
	void pasteAvailable(bool available);
	void undoAvailable(bool available);
	void redoAvailable(bool available);
	void textChanged();

	void modifiedChanged(bool modified);
	
protected:
        virtual void  itemInserted(int index);
        virtual void itemRemoved(int index);

	bool find(const QString & text, QTextDocument::FindFlags flags=0);
	
protected slots:
	void onCurrentChanged(int idx);
	void onCopyAvailable(bool available);
	void onUndoAvailable(bool available);
	void onRedoAvailable(bool available);

private:
	QFont m_font;
	
	// @@ This should be pdata, so that QTextDocument is not included in the header
	QString lastSearch;
	QTextDocument::FindFlags lastSearchOptions;
        //Highlighter *m_highlighter;
        //SourceEdit *m_sourcer;
};


class SourceEdit : public QPlainTextEdit
{
Q_OBJECT

public:
	SourceEdit(QWidget * parent = 0);
        ~SourceEdit();
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    void setHighlighter(Highlighter *highlighter);
    Highlighter* highlighter() const;
    void setCompleter(Completer* completer);
    Completer* completer() const { return m_completer; };

protected:
	void keyPressEvent(QKeyEvent * event);
        //void paintEvent(QPaintEvent * event);
        void resizeEvent(QResizeEvent *event);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
    Highlighter *m_highlighter;
    Completer *m_completer;

        //QRect lineRect();
	
//protected slots:
//	void cursorChanged();

//private:
        //int m_line;
        //QRect m_lineRect;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(SourceEdit *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    SourceEdit *codeEditor;
};

#endif // EDITOR_H
