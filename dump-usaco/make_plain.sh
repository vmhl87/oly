for file in html/*.html; do
	filename=$(basename "$file" .html)

	pandoc -f html -t plain "$file" -o "plaintext/${filename}.txt"
done
