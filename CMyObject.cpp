#include "CMyObject.hpp"

CMyObject::CMyObject(QObject *parent) :
	QObject(parent)
	, m_value(0) {

}

CMyObject::~CMyObject() {

}

int CMyObject::value() const {
	return m_value;
}

void CMyObject::setValue(int const p_val) {
	if (m_value == p_val)
		return;

	m_value = p_val;
	emit valueChanged(m_value);
}

void CMyObject::valueDetector(int) {

}
