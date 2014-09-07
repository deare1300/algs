#ifndef _BEAUTYPRO_SEQPLUS_H_
#define _BEAUTYPRO_SEQPLUS_H_

template<class T>
class SeqPlus {
	public:
		SeqPlus():num(0) { }
		SeqPlus(T num):num(num) { }
		bool hasPlus();
		void setNum(T num) { this->num = num; }
	private:
		T num;

};


template<class T>
bool SeqPlus<T>::hasPlus() {
	vector<T> res; // store all the num seq plus start
	for(T i = 2; i < num; ++i) {
		if(2*i - 1 == num) return true;
		if(2*i - 1 > num) {
			break;
		}
		for(typename vector<T>::iterator it = res.begin(); it != res.end(); ++it) {
			*it += i;
			if(*it == num) return true;
		}
		res.insert(res.begin(), 2*i-1);	
	}
	return false;
}

#endif
