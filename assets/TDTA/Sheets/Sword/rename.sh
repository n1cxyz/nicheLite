#!/usr/bin/env bash

for file in Sword_*_Template_*_*-Sheet.png; do
    # Extract parts using '_' and '-'
    # Example filename: Sword_7_Template_Attack_1_End_Left-Sheet.png

    # Remove "-Sheet.png" suffix
    base="${file%-Sheet.png}"

    # Split by underscore
    IFS='_' read -r item number _ rest <<< "$base"

    # 'rest' now contains the action and direction parts, e.g. Attack_1_End_Left
    # Extract direction as last part after last underscore
    direction="${rest##*_}"

    # Extract action by removing direction part at the end
    action="${rest%_*}"

    # Map direction abbreviations
    case $direction in
        Down) d=D ;;
        Left) d=L ;;
        Right) d=R ;;
        Up) d=U ;;
        *) d=? ;; # Unknown
    esac

    # Map action abbreviations
    case $action in
        Idle) a=I ;;
        Run) a=R ;;
        Attack_1) a=A1 ;;
        Attack_2) a=A2 ;;
        Attack_1_End) a=AE ;;
        Special_Attack) a=S ;;
        Combo_Attack_1_And_2) a=C ;;
        Take_Damage) a=T ;;
        Death) a=X ;;
        *) a=U ;; # Unknown action
    esac

    newname="${item}_${number}_${a}${d}.png"
    echo "Renaming '$file' -> '$newname'"
    mv "$file" "$newname"
done

