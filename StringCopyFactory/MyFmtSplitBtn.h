#pragma once
//#include <memory>
//#include <string>



class CMyFmtSplitBtn : public CSplitButton
{
	//����
public:
	//��ʽö��
	enum FmtType {
		INTEGER,
		FLOAT,
		LOWER_ALPHA,
		UPPER_ALPHA,
		ANY_ALPHA,
		PRINT_ALPHA,
		LOWER_STRING,
		UPPER_STRING,
		ANY_STRING,
		CHINESE,
		FmtTypeBuf
	};
	struct FmtContext {
		FmtType type = FmtTypeBuf;//ƥ��ĸ�ʽ����
		int line = 0;//���ڵ���
		int pos = -1;//��ʽƥ�������
					 //int lenPrefix = -1;//ǰ׺����
					 //int lenSuffix = -1;//��׺����
		std::shared_ptr<CMyFmtSplitBtn> spBtn = nullptr;//��ʽ���ư�ť;

		FmtContext(FmtType t, int l, int p/*int lenp, int lens*/, decltype(spBtn) sp = nullptr)
			: type(t), line(l), pos(p)/*lenPrefix(lenp), lenSuffix(lens)*/, spBtn(sp) {}
	};

	//����
	DECLARE_MESSAGE_MAP()
public:
	CMyFmtSplitBtn() {}
	CMyFmtSplitBtn(FmtType t) : m_type(t) {}

	inline void SetSize(int w, int h) { m_size.cx = w; m_size.cy = h; }
	inline const CSize& GetSize() { return m_size; }

protected:
private:
	//����
public:
protected:
	CSize				m_size;//��ť�Ŀ��
	//CMenu				m_menu;//��ť�˵�����ʼ����ȡ

private:
	FmtType				m_type;
	union {//��ʽ��ť����������
		int n;
		float f;
		char c;
		//std::string;
	};
};
