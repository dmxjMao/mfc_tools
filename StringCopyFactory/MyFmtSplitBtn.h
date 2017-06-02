#pragma once
//#include <memory>
//#include <string>
#include <boost\variant.hpp> //


class CMyFmtSplitBtn : public CSplitButton
{
	//类型声明
public:
	//格式枚举
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
	//匹配上下文
	struct FmtContext {
		FmtType type = FmtTypeBuf;//匹配的格式类型
		int line = 0;//所在的行
		int pos = -1;//格式匹配的索引
					 //int lenPrefix = -1;//前缀长度
					 //int lenSuffix = -1;//后缀长度
		std::shared_ptr<CMyFmtSplitBtn> spBtn = nullptr;//格式控制按钮;

		FmtContext(FmtType t, int l, int p/*int lenp, int lens*/, decltype(spBtn) sp = nullptr)
			: type(t), line(l), pos(p)/*lenPrefix(lenp), lenSuffix(lens)*/, spBtn(sp) {}

		~FmtContext(){
			if (spBtn) { //CMyFmtSplitBtn 绑定了菜单资源的，它不能删
				//spBtn->DestroyWindow();
				//spBtn.reset();
				//spBtn.~shared_ptr();
				spBtn->m_pMenu = nullptr;
			}
		}
	};
	//按钮参数
	struct IntParam{
		IntParam(int _a = 0,int _b = 0) : a(_a),b(_b){}
		int a = 0; int b = 0;
	};
	//struct FloatParam{};
	

	//方法
	DECLARE_MESSAGE_MAP()
public:
	CMyFmtSplitBtn() {}
	CMyFmtSplitBtn(FmtType t,int idx) : m_type(t), m_idx(idx) {}

	inline void SetSize(int w, int h) { m_size.cx = w; m_size.cy = h; }
	inline const CSize& GetSize() { return m_size; }
	//处理菜单消息
	void OnMenuMsg(UINT nID);
	static int					m_curBtn;//当前正在处理的按钮索引
	UINT						m_curID;//按钮被选择的菜单ID
	afx_msg void OnDropDown(NMHDR *pNMHDR, LRESULT *pResult);

protected:
private:
	//属性
public:
	//boost::variant<
	//	std::vector<int>,
	//	std::vector<float>,
	//	std::vector<char>,
	//	std::vector<std::string>
	//>	m_data;//格式按钮产生的数据
	boost::variant<int, float, char, std::wstring> m_data;
	//按钮参数
	boost::variant<IntParam> m_param;


protected:
	CSize				m_size;//按钮的宽高
	

private:
	FmtType				m_type;//按钮代表的类型
	int					m_idx;//按钮索引
};
