; ModuleID = 'Output/ConditionalReturn.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @ifTest(i32 %a, i32 %b) #0 {
entry:
  %add = add nsw i32 %a, 2
  %add1 = add nsw i32 %a, 3
  %cmp = icmp sgt i32 %add, 5
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %mul = mul nsw i32 %a, 2
  br label %if.end

if.else:                                          ; preds = %entry
  %mul2 = mul nsw i32 %add, 2
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret i32 %add1
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.5.1 (tags/RELEASE_351/final)"}
