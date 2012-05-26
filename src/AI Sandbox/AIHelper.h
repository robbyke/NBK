#ifndef AIHELPHER_H
#define AIHELPHER_H

#include <cml/cml.h>

namespace AI
{
	class CAIHelper
	{
	public:
		CAIHelper(void);
		~CAIHelper(void);

		struct sAbstractBlock
		{
			cml::vector2i	position;
			int				owner;

			sAbstractBlock(cml::vector2i position, int owner)
			{
				this->position = position;
				this->owner = owner;
			}
		};

		// methods each creature may use for it's AI
		// parameters ending with _ are outgoing params

		// Fills blocks_ vector with locations of currently unclaimed blocks.
		virtual void getUnclaimedBlocks(std::vector<sAbstractBlock> &blocks_) = 0;

		// Runs the threaded calculation of path-ing from 'from' to 'to' using A*.
		// Method returns immediately, results should be checked with 'pathIsReady' using an ID generated by this method.
		virtual int pathFind(cml::vector2i &from, cml::vector2i &to) = 0;

		// Call to see if the path with specified ID has already been found. 
		// If so, the results are found in 'path_'.
		virtual bool pathIsReady(int pathID, std::vector<cml::vector2i> &path_) = 0;
	};
};

#endif // AIHELPHER_H