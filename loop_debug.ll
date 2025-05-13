; ModuleID = 'MusLang'
source_filename = "MusLang"

@.str = private constant [18 x i8] c"\22Initial values:\22\00"
@.str.1 = private constant [4 x i8] c"%s\0A\00"
@.str.2 = private constant [7 x i8] c"\22i = \22\00"
@.str.3 = private constant [4 x i8] c"%s\0A\00"
@.str.4 = private constant [4 x i8] c"%f\0A\00"
@.str.5 = private constant [9 x i8] c"\22sum = \22\00"
@.str.6 = private constant [4 x i8] c"%s\0A\00"
@.str.7 = private constant [4 x i8] c"%f\0A\00"
@.str.8 = private constant [18 x i8] c"\22Loop iteration:\22\00"
@.str.9 = private constant [4 x i8] c"%s\0A\00"
@.str.10 = private constant [4 x i8] c"%f\0A\00"
@.str.11 = private constant [15 x i8] c"\22Current sum:\22\00"
@.str.12 = private constant [4 x i8] c"%s\0A\00"
@.str.13 = private constant [4 x i8] c"%f\0A\00"
@.str.14 = private constant [16 x i8] c"\22Final values:\22\00"
@.str.15 = private constant [4 x i8] c"%s\0A\00"
@.str.16 = private constant [7 x i8] c"\22i = \22\00"
@.str.17 = private constant [4 x i8] c"%s\0A\00"
@.str.18 = private constant [4 x i8] c"%f\0A\00"
@.str.19 = private constant [9 x i8] c"\22sum = \22\00"
@.str.20 = private constant [4 x i8] c"%s\0A\00"
@.str.21 = private constant [4 x i8] c"%f\0A\00"

define i32 @main() {
entry:
  %i = alloca double, align 8
  store double 0.000000e+00, ptr %i, align 8
  %sum = alloca double, align 8
  store double 0.000000e+00, ptr %sum, align 8
  %printfCall = call i32 (ptr, ...) @printf(ptr @.str.1, ptr @.str)
  %printfCall1 = call i32 (ptr, ...) @printf(ptr @.str.3, ptr @.str.2)
  %load_identifier = load double, ptr %i, align 8
  %printfCall2 = call i32 (ptr, ...) @printf(ptr @.str.4, double %load_identifier)
  %printfCall3 = call i32 (ptr, ...) @printf(ptr @.str.6, ptr @.str.5)
  %load_identifier4 = load double, ptr %sum, align 8
  %printfCall5 = call i32 (ptr, ...) @printf(ptr @.str.7, double %load_identifier4)
  %printfCall6 = call i32 (ptr, ...) @printf(ptr @.str.9, ptr @.str.8)
  %load_identifier7 = load double, ptr %i, align 8
  %printfCall8 = call i32 (ptr, ...) @printf(ptr @.str.10, double %load_identifier7)
  %load_identifier9 = load double, ptr %i, align 8
  %load_for_addition = load double, ptr %sum, align 8
  %fadd = fadd double %load_for_addition, %load_identifier9
  store double %fadd, ptr %sum, align 8
  %printfCall10 = call i32 (ptr, ...) @printf(ptr @.str.12, ptr @.str.11)
  %load_identifier11 = load double, ptr %sum, align 8
  %printfCall12 = call i32 (ptr, ...) @printf(ptr @.str.13, double %load_identifier11)
  %load_for_addition13 = load double, ptr %i, align 8
  %fadd14 = fadd double %load_for_addition13, 1.000000e+00
  store double %fadd14, ptr %i, align 8
  %loop_counter = alloca i32, align 4
  store i32 0, ptr %loop_counter, align 4
  br label %loop_header

loop_header:                                      ; preds = %loop_body, %entry
  %current_count = load i32, ptr %loop_counter, align 4
  %loop_condition = icmp slt i32 %current_count, 5
  br i1 %loop_condition, label %loop_body, label %loop_exit

loop_body:                                        ; preds = %loop_header
  %current_count15 = load i32, ptr %loop_counter, align 4
  %incremented_count = add i32 %current_count15, 1
  store i32 %incremented_count, ptr %loop_counter, align 4
  br label %loop_header

loop_exit:                                        ; preds = %loop_header
  %printfCall16 = call i32 (ptr, ...) @printf(ptr @.str.15, ptr @.str.14)
  %printfCall17 = call i32 (ptr, ...) @printf(ptr @.str.17, ptr @.str.16)
  %load_identifier18 = load double, ptr %i, align 8
  %printfCall19 = call i32 (ptr, ...) @printf(ptr @.str.18, double %load_identifier18)
  %printfCall20 = call i32 (ptr, ...) @printf(ptr @.str.20, ptr @.str.19)
  %load_identifier21 = load double, ptr %sum, align 8
  %printfCall22 = call i32 (ptr, ...) @printf(ptr @.str.21, double %load_identifier21)
  ret i32 0
}

declare i32 @printf(ptr, ...)