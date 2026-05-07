#include <opencv2/opencv.hpp>

#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

cv::Mat loadImageUnicode(const std::wstring& path)
{
    FILE* file = nullptr;

    _wfopen_s(&file, path.c_str(), L"rb");

    if (!file)
    {
        return cv::Mat();
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    std::vector<uchar> buffer(size);

    fread(buffer.data(), 1, size, file);

    fclose(file);

    return cv::imdecode(buffer, cv::IMREAD_COLOR);
}

bool saveImageUnicode(
    const std::wstring& path,
    const cv::Mat& image)
{
    std::vector<uchar> buffer;

    if (!cv::imencode(".png", image, buffer))
    {
        return false;
    }

    FILE* file = nullptr;

    _wfopen_s(&file, path.c_str(), L"wb");

    if (!file)
    {
        return false;
    }

    fwrite(buffer.data(), 1, buffer.size(), file);

    fclose(file);

    return true;
}

std::wstring makeOutputFilename(
    const std::wstring& inputFilename,
    int rows,
    int cols)
{
    std::filesystem::path path(inputFilename);

    std::wstring stem = path.stem().wstring();

    std::wstring extension = path.extension().wstring();

    return stem
        + L"_"
        + std::to_wstring(rows)
        + L"x"
        + std::to_wstring(cols)
        + extension;
}

int wmain(int argc, wchar_t* argv[])
{
    // gridder <filename>

    if (argc < 2)
    {
        std::wcout << L"Usage:\n";
        std::wcout << L"gridder <filename>\n";

        return 1;
    }

    std::wstring filename = argv[1];

    int rows = 0;
    int cols = 0;

    std::wcout << L"Input file: " << filename << std::endl << std::endl;
    std::wcout << L"Input rows and columns.\n";
    std::wcout << L"Example: 3 4\n\n";
    std::wcout << L"> ";

    std::wcin >> rows >> cols;

    if (rows <= 0 || cols <= 0)
    {
        std::wcout << L"Rows and columns must be > 0\n";
        return 1;
    }

    cv::Mat image = loadImageUnicode(filename);

    if (image.empty())
    {
        std::wcout << L"Failed to load image.\n";
        return 1;
    }

    int width = image.cols;
    int height = image.rows;

    cv::Mat overlay = image.clone();

    cv::Scalar lineColor(0, 0, 255);

    int thickness = 4;

    // ‰¡ü
    for (int y = 1; y < rows; y++)
    {
        int py = y * height / rows;

        cv::line(
            overlay,
            cv::Point(0, py),
            cv::Point(width, py),
            lineColor,
            thickness,
            cv::LINE_AA
        );
    }

    // cü
    for (int x = 1; x < cols; x++)
    {
        int px = x * width / cols;

        cv::line(
            overlay,
            cv::Point(px, 0),
            cv::Point(px, height),
            lineColor,
            thickness,
            cv::LINE_AA
        );
    }

    cv::Mat result;

    cv::addWeighted(
        overlay,
        0.5,
        image,
        0.5,
        0.0,
        result
    );

    std::wstring output =
        makeOutputFilename(filename, rows, cols);

    if (!saveImageUnicode(output, result))
    {
        std::wcout << L"Failed to save image.\n";
        return 1;
    }

    std::wcout << L"\nSaved: "
        << output
        << L"\n";

    return 0;
}