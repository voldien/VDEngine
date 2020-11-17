#ifndef _VD_NO_COPYABLE_H_
#define _VD_NO_COPYABLE_H_ 1
class NoCopyable {
private:
	NoCopyable(void);

public:
	NoCopyable(const NoCopyable &) = delete; // non construction-copyable
	NoCopyable &operator=(const NoCopyable &) = delete; // non copyable

	static NoCopyable *create();
};

#endif