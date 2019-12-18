#!/bin/sh

cd output || {
    echo "there is no output directory"
    exit 1
}

# crop graphs
for file in *.pdf; do
    pdfcrop "$file" "$file.cropped"
done
for file in *.cropped; do
    mv "$file" "$(echo "$file" | sed "s/.pdf.cropped$/.pdf/g")" 
done

# convert them to eps files
for file in *.pdf; do
    pdftops -eps "$file"
done

cd ..

# move them to the ./figures directory

mkdir -p figures

mv ./output/*.eps ./figures
