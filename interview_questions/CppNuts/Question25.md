# Static Binding / Dynamic binding

**What is Binding?**
프로그램에 사용된 식별자(함수, 변수 등)가 실제 메모리 주소와 연결되는 과정

**1) Static Binding**

- 컴파일 타임에 호출될 함수의 주소가 결정됨
- 대상: 일반 함수 호출, 함수 오버로딩, 연산자 오버로딩, Template
- 특징: 컴파일러가 호툴할 대상을 정확히 알기 떄문에 inlining 최적화가 가능함.
    - 런타임에 주소를 찾는 과정이 없어 실행 속도가 매우 빠름. 
- Zero-overhead 를 지향하는 C++의 철학에 가장 부합함. CRTP(Curiously Recurring Template Pattern) 를 사용하여 다형성을 구현하는 이유가 정적 바인딩의 속도를 얻기 위함임.

**2) Dynamic Binding**
- 런타임에 호출될 함수의 주소가 결정됨
- 대상: 가상 함수  (Virtual Functions) 호출. (`virtual` 키워드)
- 특징:
    - VTable 을 참조하여 실제 객체의 타입을 확인하고 함수를 호출함
    - 상속 관계에서 유연한 설계가 가능하지만, 약간의 오버헤드가 발생함.
- 포인터를 두 번 따라가야 하므로 캐시 미스(Cache Miss)가 발생할 확률이 높음.
    - 인라인화 방해: 컴파일러가 실행 전까지 어떤 핢수가 호출될지 모르기 때문에 이날인 최적화를 포기함.
    - 따라서 HFT의 Hot Path 구간에서는 가상 함수 사용을 극도로 자제.