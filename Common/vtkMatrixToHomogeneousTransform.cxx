/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkMatrixToHomogeneousTransform.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkMatrixToHomogeneousTransform.h"

#include "vtkMatrix4x4.h"
#include "vtkObjectFactory.h"

vtkCxxRevisionMacro(vtkMatrixToHomogeneousTransform, "1.7");
vtkStandardNewMacro(vtkMatrixToHomogeneousTransform);
vtkCxxSetObjectMacro(vtkMatrixToHomogeneousTransform,Input,vtkMatrix4x4);

//----------------------------------------------------------------------------
vtkMatrixToHomogeneousTransform::vtkMatrixToHomogeneousTransform()
{
  this->Input = NULL;
  this->InverseFlag = 0;
}

//----------------------------------------------------------------------------
vtkMatrixToHomogeneousTransform::~vtkMatrixToHomogeneousTransform()
{
  this->SetInput(NULL);
}

//----------------------------------------------------------------------------
void vtkMatrixToHomogeneousTransform::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Update();

  this->Superclass::PrintSelf(os, indent);
  os << indent << "Input: " << this->Input << "\n";
  os << indent << "InverseFlag: " << this->InverseFlag << "\n";
}

//----------------------------------------------------------------------------
void vtkMatrixToHomogeneousTransform::Inverse()
{
  this->InverseFlag = !this->InverseFlag;
  this->Modified();
}

//----------------------------------------------------------------------------
void vtkMatrixToHomogeneousTransform::InternalUpdate()
{
  if (this->Input)
    {
    this->Matrix->DeepCopy(this->Input);
    if (this->InverseFlag)
      {
      this->Matrix->Invert();
      }
    }
  else
    {
    this->Matrix->Identity();
    }
}

//----------------------------------------------------------------------------
void vtkMatrixToHomogeneousTransform::InternalDeepCopy(
                                                vtkAbstractTransform *gtrans)
{
  vtkMatrixToHomogeneousTransform *transform = 
    (vtkMatrixToHomogeneousTransform *)gtrans;

  this->SetInput(transform->Input);

  if (this->InverseFlag != transform->InverseFlag)
    {
    this->Inverse();
    }
}

//----------------------------------------------------------------------------
vtkAbstractTransform *vtkMatrixToHomogeneousTransform::MakeTransform()
{
  return vtkMatrixToHomogeneousTransform::New();
}

//----------------------------------------------------------------------------
// Get the MTime
unsigned long vtkMatrixToHomogeneousTransform::GetMTime()
{
  unsigned long mtime = this->vtkHomogeneousTransform::GetMTime();

  if (this->Input)
    {
    unsigned long matrixMTime = this->Input->GetMTime();
    if (matrixMTime > mtime)
      {
      return matrixMTime;
      }
    }
  return mtime;
}
