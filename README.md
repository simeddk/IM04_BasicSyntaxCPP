### 1. 스크린샷
![image](https://github.com/user-attachments/assets/fd800e7a-78a6-458e-a848-538369663af4)

### 2. 구현된 기능
- 딜리게이트 실습(Delegate, Event, Multicast, DynamicDelegate)
- 블루프린트 오버라이드(BlueprintImplemetableEvent, BlueprintNativeEvent)
  - BlueprintImplemetableEvent : 몸체의 구현을 블루프린트에서 재정의 하는 것
  - BlueprintNativeEvent : C++에서 기본적인 몸체를 구현하고 블루프린트에서 재정의가 가능함
  ```c++
  void ACAR4::Unequip()
  {
	  if (!bEquipped) return;
	  if (bPlayingMontage) return;

	  if (bAutoFiring)
	  {
		  OffFire();
	  }

	  bPlayingMontage = true;
	  OwnerCharacter->PlayAnimMontage(UnequipMontage, MontagesPlayRate);
  }
  ```
