#include "DecodeHtmlFunctions.h"

std::optional<char> GetDecodedHtmlElement(const std::string& encodedValue)
{
    // объявить в безымянном пространстве имен
	HTMLElement htmlElements[5] = {
		{ '"', "&quot;" },
		{ '\'', "&apos;" },
		{ '<', "&lt;" },
		{ '>', "&gt;" },
		{ '&', "&amp;" },
	};

	for (HTMLElement& item : htmlElements)
	{
		if (item.encodedValue == encodedValue)
		{
			return item.decodeValue;
		}
	}
	return std::nullopt;
}

void JoinDecodedHtml(std::string& encodedHtml, const std::string& encodedValue)
{
	std::optional<char> htmlElement = GetDecodedHtmlElement(encodedValue);

	if (htmlElement)
	{
		encodedHtml += htmlElement.value();
	}
	else
	{
		encodedHtml += encodedValue;
	}
}

std::string HtmlDecode(std::string& html)
{
	std::string decodedHtml;
	size_t startPosition = 0;
    bool isMnemonic = false;

	for (size_t i = 0; i < html.length(); i++)
	{
		if (isMnemonic)
		{
			if (html[i] == '&')
			{
				decodedHtml.append(html, startPosition, i - startPosition);
				startPosition = i;
                // попробовать уменьшить количество continue
				continue;
			}

			if (html[i] == ';')
			{
                // избавиться от копирования использовать  string_view
				std::string encodedValue(&html[startPosition], i - startPosition + 1);
				JoinDecodedHtml(decodedHtml, encodedValue);
                isMnemonic = false;
			}
			continue;
		}

		if (html[i] != '&')
		{
			decodedHtml.push_back(html[i]);
		} else {
            isMnemonic = true;
            startPosition = i;
        }
	}

	if(isMnemonic)
	{
		decodedHtml.append(html, startPosition);
	}

	return decodedHtml;
}
