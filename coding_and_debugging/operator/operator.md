### Traits of < operator
- 비반사성 (irreflexibility): a < a 는 항상 거짓
- 비대칭성 (asymmetry): a < b 가 참이면, b < a 는 거짓
- 전이성 (transivity): a < b 이고 b < c 이면, a < c 이다
- 상등 관계의 전이성 (transivity of equivalence) a < b 와 b < a 가 모두 거짓이면 a와 b는 같은 값으로 간주한다. a 와 b 가 같고, b 와 c 가 같다면, a 와 c 는 같은 값으로 간주한다.

그래서 해당 operator 를 override 할 때는 위의 4가지 특징이 모두 성립하도록 override 해줘야 한다.