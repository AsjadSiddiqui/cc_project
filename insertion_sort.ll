; ModuleID = 'MusLang'
source_filename = "MusLang"

@.str = private constant [18 x i8] c"\22Original array:\22\00"
@.str.1 = private constant [4 x i8] c"%s\0A\00"
@.str.2 = private constant [4 x i8] c"%f\0A\00"
@.str.3 = private constant [4 x i8] c"%f\0A\00"
@.str.4 = private constant [4 x i8] c"%f\0A\00"
@.str.5 = private constant [4 x i8] c"%f\0A\00"
@.str.6 = private constant [4 x i8] c"%f\0A\00"
@.str.7 = private constant [29 x i8] c"\22Starting insertion sort...\22\00"
@.str.8 = private constant [4 x i8] c"%s\0A\00"
@.str.9 = private constant [43 x i8] c"\22Step 1: Sort elements at indices 0 and 1\22\00"
@.str.10 = private constant [4 x i8] c"%s\0A\00"
@.str.11 = private constant [16 x i8] c"\22After step 1:\22\00"
@.str.12 = private constant [4 x i8] c"%s\0A\00"
@.str.13 = private constant [4 x i8] c"%f\0A\00"
@.str.14 = private constant [4 x i8] c"%f\0A\00"
@.str.15 = private constant [4 x i8] c"%f\0A\00"
@.str.16 = private constant [4 x i8] c"%f\0A\00"
@.str.17 = private constant [4 x i8] c"%f\0A\00"
@.str.18 = private constant [36 x i8] c"\22Step 2: Insert element at index 2\22\00"
@.str.19 = private constant [4 x i8] c"%s\0A\00"
@.str.20 = private constant [16 x i8] c"\22After step 2:\22\00"
@.str.21 = private constant [4 x i8] c"%s\0A\00"
@.str.22 = private constant [4 x i8] c"%f\0A\00"
@.str.23 = private constant [4 x i8] c"%f\0A\00"
@.str.24 = private constant [4 x i8] c"%f\0A\00"
@.str.25 = private constant [4 x i8] c"%f\0A\00"
@.str.26 = private constant [4 x i8] c"%f\0A\00"
@.str.27 = private constant [36 x i8] c"\22Step 3: Insert element at index 3\22\00"
@.str.28 = private constant [4 x i8] c"%s\0A\00"

define i32 @main() {
entry:
  %a0 = alloca double, align 8
  store double 5.000000e+00, ptr %a0, align 8
  %a1 = alloca double, align 8
  store double 2.000000e+00, ptr %a1, align 8
  %a2 = alloca double, align 8
  store double 4.000000e+00, ptr %a2, align 8
  %a3 = alloca double, align 8
  store double 1.000000e+00, ptr %a3, align 8
  %a4 = alloca double, align 8
  store double 3.000000e+00, ptr %a4, align 8
  %printfCall = call i32 (ptr, ...) @printf(ptr @.str.1, ptr @.str)
  %load_identifier = load double, ptr %a0, align 8
  %printfCall1 = call i32 (ptr, ...) @printf(ptr @.str.2, double %load_identifier)
  %load_identifier2 = load double, ptr %a1, align 8
  %printfCall3 = call i32 (ptr, ...) @printf(ptr @.str.3, double %load_identifier2)
  %load_identifier4 = load double, ptr %a2, align 8
  %printfCall5 = call i32 (ptr, ...) @printf(ptr @.str.4, double %load_identifier4)
  %load_identifier6 = load double, ptr %a3, align 8
  %printfCall7 = call i32 (ptr, ...) @printf(ptr @.str.5, double %load_identifier6)
  %load_identifier8 = load double, ptr %a4, align 8
  %printfCall9 = call i32 (ptr, ...) @printf(ptr @.str.6, double %load_identifier8)
  %load_identifier10 = load double, ptr %a0, align 8
  %v0 = alloca double, align 8
  store double %load_identifier10, ptr %v0, align 8
  %load_identifier11 = load double, ptr %a1, align 8
  %v1 = alloca double, align 8
  store double %load_identifier11, ptr %v1, align 8
  %load_identifier12 = load double, ptr %a2, align 8
  %v2 = alloca double, align 8
  store double %load_identifier12, ptr %v2, align 8
  %load_identifier13 = load double, ptr %a3, align 8
  %v3 = alloca double, align 8
  store double %load_identifier13, ptr %v3, align 8
  %load_identifier14 = load double, ptr %a4, align 8
  %v4 = alloca double, align 8
  store double %load_identifier14, ptr %v4, align 8
  %temp = alloca double, align 8
  store double 0.000000e+00, ptr %temp, align 8
  %printfCall15 = call i32 (ptr, ...) @printf(ptr @.str.8, ptr @.str.7)
  %printfCall16 = call i32 (ptr, ...) @printf(ptr @.str.10, ptr @.str.9)
  %load_identifier17 = load double, ptr %v0, align 8
  %load_identifier18 = load double, ptr %v1, align 8
  %comparison = fcmp ogt double %load_identifier17, %load_identifier18
  %boolToDouble = uitofp i1 %comparison to double
  %load_identifier19 = load double, ptr %v0, align 8
  store double %load_identifier19, ptr %temp, align 8
  %load_identifier20 = load double, ptr %v1, align 8
  store double %load_identifier20, ptr %v0, align 8
  %load_identifier21 = load double, ptr %temp, align 8
  store double %load_identifier21, ptr %v1, align 8
  %printfCall22 = call i32 (ptr, ...) @printf(ptr @.str.12, ptr @.str.11)
  %load_identifier23 = load double, ptr %v0, align 8
  %printfCall24 = call i32 (ptr, ...) @printf(ptr @.str.13, double %load_identifier23)
  %load_identifier25 = load double, ptr %v1, align 8
  %printfCall26 = call i32 (ptr, ...) @printf(ptr @.str.14, double %load_identifier25)
  %load_identifier27 = load double, ptr %v2, align 8
  %printfCall28 = call i32 (ptr, ...) @printf(ptr @.str.15, double %load_identifier27)
  %load_identifier29 = load double, ptr %v3, align 8
  %printfCall30 = call i32 (ptr, ...) @printf(ptr @.str.16, double %load_identifier29)
  %load_identifier31 = load double, ptr %v4, align 8
  %printfCall32 = call i32 (ptr, ...) @printf(ptr @.str.17, double %load_identifier31)
  %printfCall33 = call i32 (ptr, ...) @printf(ptr @.str.19, ptr @.str.18)
  %load_identifier34 = load double, ptr %v2, align 8
  %key = alloca double, align 8
  store double %load_identifier34, ptr %key, align 8
  %load_identifier35 = load double, ptr %key, align 8
  %load_identifier36 = load double, ptr %v1, align 8
  %comparison37 = fcmp ogt double %load_identifier35, %load_identifier36
  %boolToDouble38 = uitofp i1 %comparison37 to double
  %load_identifier39 = load double, ptr %v1, align 8
  store double %load_identifier39, ptr %v2, align 8
  %load_identifier40 = load double, ptr %key, align 8
  store double %load_identifier40, ptr %v1, align 8
  %printfCall41 = call i32 (ptr, ...) @printf(ptr @.str.21, ptr @.str.20)
  %load_identifier42 = load double, ptr %v0, align 8
  %printfCall43 = call i32 (ptr, ...) @printf(ptr @.str.22, double %load_identifier42)
  %load_identifier44 = load double, ptr %v1, align 8
  %printfCall45 = call i32 (ptr, ...) @printf(ptr @.str.23, double %load_identifier44)
  %load_identifier46 = load double, ptr %v2, align 8
  %printfCall47 = call i32 (ptr, ...) @printf(ptr @.str.24, double %load_identifier46)
  %load_identifier48 = load double, ptr %v3, align 8
  %printfCall49 = call i32 (ptr, ...) @printf(ptr @.str.25, double %load_identifier48)
  %load_identifier50 = load double, ptr %v4, align 8
  %printfCall51 = call i32 (ptr, ...) @printf(ptr @.str.26, double %load_identifier50)
  %printfCall52 = call i32 (ptr, ...) @printf(ptr @.str.28, ptr @.str.27)
  %load_identifier53 = load double, ptr %v3, align 8
  store double %load_identifier53, ptr %key, align 8
  %load_identifier54 = load double, ptr %v2, align 8
  store double %load_identifier54, ptr %v3, align 8
  %load_identifier55 = load double, ptr %v1, align 8
  store double %load_identifier55, ptr %v2, align 8
  %load_identifier56 = load double, ptr %v0, align 8
  store double %load_identifier56, ptr %v1, align 8
  ret i32 0
}

declare i32 @printf(ptr, ...)