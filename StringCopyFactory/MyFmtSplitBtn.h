#pragma once
//#include <memory>
//#include <string>
#include <boost\variant.hpp> //


class CMyFmtSplitBtn : public CSplitButton
{
	//��������
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
	//ƥ��������
	struct FmtContext {
		FmtType type = FmtTypeBuf;//ƥ��ĸ�ʽ����
		int line = 0;//���ڵ���
		int pos = -1;//��ʽƥ�������
					 //int lenPrefix = -1;//ǰ׺����
					 //int lenSuffix = -1;//��׺����
		std::shared_ptr<CMyFmtSplitBtn> spBtn = nullptr;//��ʽ���ư�ť;

		FmtContext(FmtType t, int l, int p/*int lenp, int lens*/, decltype(spBtn) sp = nullptr)
			: type(t), line(l), pos(p)/*lenPrefix(lenp), lenSuffix(lens)*/, spBtn(sp) {}

		~FmtContext(){
			if (spBtn) { //CMyFmtSplitBtn ���˲˵���Դ�ģ�������ɾ
				//spBtn->DestroyWindow();
				//spBtn.reset();
				//spBtn.~shared_ptr();
				spBtn->m_pMenu = nullptr;
			}
		}
	};
	//��ť����
	struct IntParam{
		IntParam(int _a = 0,int _b = 0) : a(_a),b(_b){}
		int a = 0; int b = 0;
	};
	//struct FloatParam{};
	

	//����
	DECLARE_MESSAGE_MAP()
public:
	CMyFmtSplitBtn() {}
	CMyFmtSplitBtn(FmtType t,int idx) : m_type(t), m_idx(idx) {}

	inline void SetSize(int w, int h) { m_size.cx = w; m_size.cy = h; }
	inline const CSize& GetSize() { return m_size; }
	//����˵���Ϣ
	void OnMenuMsg(UINT nID);
	static int					m_curBtn;//��ǰ���ڴ���İ�ť����
	UINT						m_curID;//��ť��ѡ��Ĳ˵�ID
	afx_msg void OnDropDown(NMHDR *pNMHDR, LRESULT *pResult);

protected:
private:
	//����
public:
	//boost::variant<
	//	std::vector<int>,
	//	std::vector<float>,
	//	std::vector<char>,
	//	std::vector<std::string>
	//>	m_data;//��ʽ��ť����������
	boost::variant<int, float, char, std::wstring> m_data;
	//��ť����
	boost::variant<IntParam> m_param;


protected:
	CSize				m_size;//��ť�Ŀ��
	

private:
	FmtType				m_type;//��ť���������
	int					m_idx;//��ť����
};
