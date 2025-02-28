// Copyright Frinky 2022


#include "FC_SurfaceDataAsset.h"

FSurfaceData UFC_SurfaceDataAsset::GetDataFromPhysicalMaterial(UPhysicalMaterial* HitMaterial)
{
	if(!HitMaterial) return Surfaces[0];
	for (FSurfaceData SurfaceData : Surfaces)
	{
		if(SurfaceData.Material->GetClass() == HitMaterial->GetClass())
		{
			return SurfaceData;
		}
	}

	return Surfaces[0];
}

FSurfaceData UFC_SurfaceDataAsset::GetDataFromHitResult(FHitResult HitResult)
{
	// If no hit result, return the first surface
	if(!HitResult.PhysMaterial.Get()) return Surfaces[0];
	
	for (FSurfaceData SurfaceData : Surfaces)
	{
		if(SurfaceData.Material->GetName() == HitResult.PhysMaterial->GetName() )
		{
			return SurfaceData;
		}
	}
	
	return Surfaces[0];
}
