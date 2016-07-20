#ifndef __SFL_SEQUENCE_FACE_LANDMARKS__
#define __SFL_SEQUENCE_FACE_LANDMARKS__

// std
#include <string>
#include <list>
#include <memory>

// OpenCV
#include <opencv2/core.hpp>

namespace sfl
{
	/** @brief Represents a face detected in a frame.
	*/
    struct Face
    {
		int id;								///< Face id.
		cv::Rect bbox;						///< Bounding box.
        std::vector<cv::Point> landmarks;	///< Face landmarks.
		
    };

	/** @brief Represents a frame that might include faces.
	*/
    struct Frame
    {
		int id;						///< Frame id.
		int width;					///< Frame width [pixels]
		int height;					///< Frame height [pixels]
        std::list<std::unique_ptr<Face>> faces;	///< Detected faces in the frame
    };

	/** @brief Interface for sequence face landmarks functionality.

	This class provide face landmarks functionality over a sequence of frames.
	*/
	class SequenceFaceLandmarks
	{
	public:

		/** @brief Add a frame to process.
		@param frame The frame to process [BGR|Grayscale].
		@param id Frame id. If negative, an internal counter will be used instead.
		*/
		virtual const Frame& addFrame(const cv::Mat& frame, int id = -1) = 0;

		/** @brief Get the frame sequence with all landmarks and bounding boxes 
		for each detected face.
		*/
		virtual const std::list<std::unique_ptr<Frame>>& getSequence() const = 0;

		/** @brief Clear all processed or loaded data.
		*/
		virtual void clear() = 0;

		/** @brief Create a full copy, loaded face detector and landmark model 
		will be shared.
		*/
		virtual std::shared_ptr<SequenceFaceLandmarks> clone() = 0;

		/** @brief Get landmarks model file.
		*/
		virtual std::string getModel() const = 0;

		/** @brief Get frame scale.
		*/
		virtual float getFrameScale() const = 0;

		/** @brief Get if tracking faces is enabled or disabled.
		*/
		virtual bool getTrackFaces() const = 0;

		/** @brief Load a sequence of face landmarks from file.
		*/
		virtual void load(const std::string& filePath) = 0;

		/** @brief Save current sequence of face landmarks to file.
		*/
		virtual void save(const std::string& filePath) const = 0;

		/** @brief Set frame scale.
		*/
		virtual void setFrameScale(float frame_scale) = 0;

		/** @brief Set landmarks model file.
		*/
		virtual void setModel(const std::string& modelPath) = 0;

		/** @brief Enable\disable tracking faces across the sequence of frames.
			This will keep the face ids consistent in the sequence.
		*/
		virtual void setTrackFaces(bool track_faces) = 0;
		
		/** @brief Get the number of the current frames.
		*/
		virtual size_t size() const = 0;

		/** @brief Create an instance initialized with a landmarks model file.
		@param modelPath The landmarks model file.
		@frame_scale Each frame will be scaled by this factor. Useful for detection of small
		faces. The landmarks will still be in the original frame's pixel coordinates.
		*/
		static std::shared_ptr<SequenceFaceLandmarks> create(
			const std::string& modelPath, float frame_scale = 1.0f,
			bool track_faces = false);

		/** @brief Create an instance.
		@frame_scale Each frame will be scaled by this factor. Useful for detection of small
		faces. The landmarks will still be in the original frame's pixel coordinates.
		*/
		static std::shared_ptr<SequenceFaceLandmarks> create(
			float frame_scale = 1.0f, bool track_faces = false);
	};

	/** @brief Render landmarks.
	@param img The image that the landmarks will be rendered on.
	@param landmarks The landmark points to render.
	@param drawLabels if true, for each landmark, it's 0 based index will be 
	rendererd as a label.
	@param color Line\point and label color.
	@param thickness Line\point thickness.
	*/
	void render(cv::Mat& img, const std::vector<cv::Point>& landmarks,
		bool drawLabels = false, const cv::Scalar& color = cv::Scalar(0, 255, 0),
		int thickness = 1);

	/** @brief Render bounding box.
	@param img The image that the bounding box will be rendered on.
	@param bbox The bounding box rectangle to render.
	@param color Line color.
	@param thickness Line thickness.
	*/
	void render(cv::Mat& img, const cv::Rect& bbox,
		const cv::Scalar& color = cv::Scalar(0, 255, 0), int thickness = 1);

	/** @brief Render face's bounding box and landmarks.
	@param img The image that the face will be rendered on.
	@param face The face to render.
	@param drawLabels if true, for each landmark, it's 0 based index will be
	rendererd as a label.
	@param bbox_color Bounding box line color.
	@param landmarks_color Landmarks line\point and label color.
	@param thickness Line\point thickness.
	*/
	void render(cv::Mat& img, const Face& face, bool drawLabels = false,
		const cv::Scalar& bbox_color = cv::Scalar(0, 0, 255),
		const cv::Scalar& landmarks_color = cv::Scalar(0, 255, 0), int thickness = 1);

	/** @brief Render all frame faces including bounding boxs and landmarks.
	@param img The image that the faces will be rendered on.
	@param frame The frame to render.
	@param drawLabels if true, for each landmark, it's 0 based index will be
	rendererd as a label.
	@param bbox_color Bounding box line color.
	@param landmarks_color Landmarks line\point and label color.
	@param thickness Line\point thickness.
	*/
	void render(cv::Mat& img, const Frame& frame, bool drawLabels = false,
		const cv::Scalar& bbox_color = cv::Scalar(0, 0, 255),
		const cv::Scalar& landmarks_color = cv::Scalar(0, 255, 0), int thickness = 1);

}   // namespace sfl

#endif	// __SFL_SEQUENCE_FACE_LANDMARKS__
