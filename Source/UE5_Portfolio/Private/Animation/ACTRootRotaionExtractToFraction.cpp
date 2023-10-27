// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ACTRootRotaionExtractToFraction.h"
#include "Kismet/KismetMathLibrary.h"

void UACTRootRotaionExtractToFraction::OnApply_Implementation(UAnimSequence* AnimationSequence)
{
	if (!AnimationSequence || !AnimationSequence->GetSkeleton()) { return; }

	UAnimationBlueprintLibrary::AddCurve(AnimationSequence, TEXT("RotationYaw"));

	int32 NumFrames{ AnimationSequence->GetNumberOfSampledKeys() };

	TArray<FTransform> Track;
	AnimationSequence->GetDataModelInterface()->GetBoneTrackTransforms(TEXT("root"), Track);
	double LastFrameYawValue{ Track.Top().Rotator().Yaw };

	for (int32 CurrentFrame{ 0 }; CurrentFrame < Track.Num(); ++CurrentFrame) {
		double CurrentYawValue{ Track[CurrentFrame].Rotator().Yaw};

		float ResultTime;
		UAnimationBlueprintLibrary::GetTimeAtFrame(AnimationSequence, CurrentFrame, ResultTime);

		double CurveKeyValue{ UKismetMathLibrary::MapRangeClamped(CurrentYawValue, 0.0, LastFrameYawValue, 0.0, 1.0) };

		UAnimationBlueprintLibrary::AddFloatCurveKey(AnimationSequence, TEXT("RotationYaw"), ResultTime, CurveKeyValue);
	}
}
