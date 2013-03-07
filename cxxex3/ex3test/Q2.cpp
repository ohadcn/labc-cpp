class Rational {

public:

  Rational(int p, int q) : _p(p), _q(q) {}
  Rational operator+(Rational &other)
  {
    Rational res(*this);
    res._p *= other._q;
    other._p *= res._q;
    res._q *= other._q;
    res._p += other._p;
    return res;
  }

  bool operator==(Rational &oth)
  {

  	return oth._q*this->_p==this->_q*oth._p;
  }
  //additional operators, including correct operator ==

private:
  int _p;
  int _q;
  // the only data members of this class

};

int main()
{
  Rational r1(7,2);
  Rational r2(14,2);
  Rational r3 = r1 + r2;
  Rational r4 = r2 + r1;

  if (r3 == r4)
    {
      //
    }

  return 0;
}
