// Fill out your copyright notice in the Description page of Project Settings.


#include "AT_AttributeChange.h"
#include "AbilitySystemComponent.h"


UAT_AttributeChange::UAT_AttributeChange(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	TriggerOnce=false;
}

//重写Activate
void UAT_AttributeChange::Activate()
{
	if(IsValid(AbilitySystemComponent) && Attribute.IsValid() )
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this,&UAT_AttributeChange::OnAttributeChanged);
	}

	Super::Activate();
}



/*
 * 这里的功能是创建Ability Task的instance，这里的函数名就是我们创建Task时实际使用的名字。
 * 函数的变量则是任务的输入。
 * 这里有个问题，就是实际上Ability Task不需要我手动赋值AbilitySystemComponent，所以这个变量可以去掉。
 */
UAT_AttributeChange* UAT_AttributeChange::ListenForAttributeChange(UGameplayAbility* OwningAbility, bool TriggerOnce,
	UAbilitySystemComponent* SystemComponent, FGameplayAttribute Attribute)
{
	UAT_AttributeChange* MyObj=NewAbilityTask<UAT_AttributeChange>(OwningAbility);
	MyObj->TriggerOnce = TriggerOnce;
	MyObj->AbilitySystemComponent=SystemComponent;
	MyObj->Attribute =Attribute;

	return MyObj;
}

// OnAttributeChanged的逻辑很简单，通过之前创建的delegate将改变的属性广播出去。如果设置过只触发一次，就调用EndTask()
void UAT_AttributeChange::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	AttributeChange.Broadcast(Data.Attribute,Data.NewValue,Data.OldValue);
	if(TriggerOnce)
	{
		EndTask();
	}
}

//这部分负责重写销毁Task的方法，首先我们需要将绑定的Uobject全部移除，然后调用父类的Destroy()函数
void UAT_AttributeChange::OnDestroy(bool bInOwnerFinished)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
	}
	
	Super::OnDestroy(bInOwnerFinished);
}
