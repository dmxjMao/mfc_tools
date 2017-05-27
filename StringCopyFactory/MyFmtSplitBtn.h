#pragma once
//#include <memory>
//#include <string>



class CMyFmtSplitBtn : public CSplitButton
{
	//定义
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
	struct FmtContext {
		FmtType type = FmtTypeBuf;//匹配的格式类型
		int line = 0;//所在的行
		int pos = -1;//格式匹配的索引
					 //int lenPrefix = -1;//前缀长度
					 //int lenSuffix = -1;//后缀长度
		std::shared_ptr<CMyFmtSplitBtn> spBtn = nullptr;//格式控制按钮;

		FmtContext(FmtType t, int l, int p/*int lenp, int lens*/, decltype(spBtn) sp = nullptr)
			: type(t), line(l), pos(p)/*lenPrefix(lenp), lenSuffix(lens)*/, spBtn(sp) {}
	};

	//方法
	DECLARE_MESSAGE_MAP()
public:
	CMyFmtSplitBtn() {}
	CMyFmtSplitBtn(FmtType t) : m_type(t) {}

	inline void SetSize(int w, int h) { m_size.cx = w; m_size.cy = h; }
	inline const CSize& GetSize() { return m_size; }

protected:
private:
	//属性
public:
protected:
	CSize				m_size;//按钮的宽高
	//CMenu				m_menu;//按钮菜单，初始化读取

private:
	FmtType				m_type;
	union {//格式按钮产生的数据
		int n;
		float f;
		char c;
		//std::string;
	};
};
