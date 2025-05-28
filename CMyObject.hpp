#include <QObject>

class CMyObject :
	public QObject
{
	Q_OBJECT;
	Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged);

public:
	~CMyObject();
	CMyObject(QObject *parent = nullptr);

	int value() const;
	void setValue(int const val);

signals:
	void valueChanged(int);

public slots:
	void valueDetector(int);

private:
	int m_value;
};
